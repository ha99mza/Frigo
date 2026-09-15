#include "networkmanager.h"

#include <QProcess>
#include <QStandardPaths>
#include <QStringList>

namespace {

// Runs nmcli synchronously and returns its stdout. Calls are individually
// fast (nmcli talks to NetworkManager over D-Bus internally, typically well
// under 100ms), and this only runs on a background poll timer / explicit
// user actions, so the brief blocking is an acceptable tradeoff for keeping
// the control flow simple.
QString runNmcli(const QStringList &args, int timeoutMs = 3000)
{
    QProcess p;
    p.start(QStringLiteral("nmcli"), args);
    if (!p.waitForFinished(timeoutMs))
        return QString();
    return QString::fromUtf8(p.readAllStandardOutput());
}

QString prefixToMask(int prefix)
{
    if (prefix < 0 || prefix > 32)
        return QString();
    quint32 mask = prefix == 0 ? 0 : (0xFFFFFFFFu << (32 - prefix));
    return QStringLiteral("%1.%2.%3.%4")
        .arg((mask >> 24) & 0xFF).arg((mask >> 16) & 0xFF)
        .arg((mask >> 8) & 0xFF).arg(mask & 0xFF);
}

} // namespace

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    m_available = !QStandardPaths::findExecutable(QStringLiteral("nmcli")).isEmpty();
    emit availableChanged();

    if (!m_available)
        return;

    m_pollTimer.setInterval(5000);
    connect(&m_pollTimer, &QTimer::timeout, this, &NetworkManager::refresh);
    m_pollTimer.start();
    refresh();
}

void NetworkManager::setBusy(bool b)
{
    if (b == m_busy) return;
    m_busy = b;
    emit busyChanged();
}

void NetworkManager::refresh()
{
    if (!m_available)
        return;
    applyStatus();
}

void NetworkManager::applyStatus()
{
    const QString radio = runNmcli({ QStringLiteral("radio"), QStringLiteral("wifi") }).trimmed();
    const bool wifiEnabled = (radio == QStringLiteral("enabled"));

    QString device, connName;
    bool wifiConnected = false;
    const QString devStatus = runNmcli({ QStringLiteral("-t"), QStringLiteral("-f"),
                                          QStringLiteral("DEVICE,TYPE,STATE,CONNECTION"),
                                          QStringLiteral("device"), QStringLiteral("status") });
    for (const QString &line : devStatus.split(QLatin1Char('\n'), Qt::SkipEmptyParts)) {
        const QStringList cols = line.split(QLatin1Char(':'));
        if (cols.size() < 4 || cols[1] != QStringLiteral("wifi"))
            continue;
        device = cols[0];
        wifiConnected = cols[2].startsWith(QStringLiteral("connected"));
        connName = cols[3];
        break;
    }

    QString ip, gateway, mask, mac;
    int signal = 0;
    QString ssid = wifiConnected ? connName : QString();

    if (!device.isEmpty() && wifiConnected) {
        const QString details = runNmcli({ QStringLiteral("-t"), QStringLiteral("-f"),
                                            QStringLiteral("GENERAL.HWADDR,IP4.ADDRESS,IP4.GATEWAY"),
                                            QStringLiteral("device"), QStringLiteral("show"), device });
        for (const QString &line : details.split(QLatin1Char('\n'), Qt::SkipEmptyParts)) {
            const int sep = line.indexOf(QLatin1Char(':'));
            if (sep < 0) continue;
            const QString key = line.left(sep);
            const QString val = line.mid(sep + 1);
            if (key == QStringLiteral("GENERAL.HWADDR")) {
                mac = val;
            } else if (key == QStringLiteral("IP4.ADDRESS[1]")) {
                const QStringList parts = val.split(QLatin1Char('/'));
                ip = parts.value(0);
                mask = prefixToMask(parts.value(1).toInt());
            } else if (key == QStringLiteral("IP4.GATEWAY")) {
                gateway = val;
            }
        }

        const QString wifiList = runNmcli({ QStringLiteral("-t"), QStringLiteral("-f"),
                                             QStringLiteral("IN-USE,SIGNAL"),
                                             QStringLiteral("device"), QStringLiteral("wifi"), QStringLiteral("list"),
                                             QStringLiteral("ifname"), device });
        for (const QString &line : wifiList.split(QLatin1Char('\n'), Qt::SkipEmptyParts)) {
            if (line.startsWith(QLatin1Char('*'))) {
                signal = line.section(QLatin1Char(':'), 1, 1).toInt();
                break;
            }
        }
    }

    m_wifiDevice = device;
    m_activeConnName = connName;

    const bool changed = m_wifiEnabled != wifiEnabled || m_wifiConnected != wifiConnected
        || m_ssid != ssid || m_ip != ip || m_gateway != gateway || m_mask != mask
        || m_mac != mac || m_signal != signal;

    m_wifiEnabled = wifiEnabled;
    m_wifiConnected = wifiConnected;
    m_ssid = ssid;
    m_ip = ip;
    m_gateway = gateway;
    m_mask = mask;
    m_mac = mac;
    m_signal = signal;

    if (changed)
        emit statusChanged();
}

void NetworkManager::setWifiEnabled(bool on)
{
    if (!m_available)
        return;
    runNmcli({ QStringLiteral("radio"), QStringLiteral("wifi"), on ? QStringLiteral("on") : QStringLiteral("off") });
    refresh();
}

void NetworkManager::rescan()
{
    if (!m_available)
        return;
    runNmcli({ QStringLiteral("device"), QStringLiteral("wifi"), QStringLiteral("rescan") });
    // A scan takes a couple of seconds to populate; the next regular poll
    // (or a manual one shortly after) will pick up fresh results.
    QTimer::singleShot(2000, this, &NetworkManager::refresh);
}

void NetworkManager::renewIp()
{
    if (!m_available || m_activeConnName.isEmpty())
        return;
    setBusy(true);

    auto *down = new QProcess(this);
    connect(down, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this,
            [this, down](int, QProcess::ExitStatus) {
        down->deleteLater();
        auto *up = new QProcess(this);
        connect(up, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this,
                [this, up](int, QProcess::ExitStatus) {
            up->deleteLater();
            setBusy(false);
            refresh();
        });
        up->start(QStringLiteral("nmcli"), { QStringLiteral("connection"), QStringLiteral("up"), m_activeConnName });
    });
    down->start(QStringLiteral("nmcli"), { QStringLiteral("connection"), QStringLiteral("down"), m_activeConnName });
}
