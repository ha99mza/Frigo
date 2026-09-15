#include "historystore.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <algorithm>
#include <limits>

namespace {
constexpr qint64 kRetentionSeconds = 8 * 24 * 3600; // keep a little over the longest UI range (7j)
}

HistoryStore::HistoryStore(QObject *parent)
    : QObject(parent)
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    m_tempLogPath = dir + QStringLiteral("/temp_history.log");
    m_defrostLogPath = dir + QStringLiteral("/defrost_events.log");
    loadAndPrune();
}

qint64 HistoryStore::windowSeconds(const QString &range)
{
    if (range == QStringLiteral("1h")) return 3600;
    if (range == QStringLiteral("7j")) return 7 * 24 * 3600;
    return 24 * 3600; // "24h" and default
}

void HistoryStore::loadAndPrune()
{
    const qint64 cutoff = QDateTime::currentSecsSinceEpoch() - kRetentionSeconds;

    QFile tf(m_tempLogPath);
    if (tf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&tf);
        while (!in.atEnd()) {
            const QStringList parts = in.readLine().split(QLatin1Char(';'));
            if (parts.size() != 2)
                continue;
            bool ok1 = false, ok2 = false;
            const qint64 t = parts[0].toLongLong(&ok1);
            const double v = parts[1].toDouble(&ok2);
            if (ok1 && ok2 && t >= cutoff)
                m_tempSamples.append({ t, v });
        }
        tf.close();
    }

    QFile df(m_defrostLogPath);
    if (df.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&df);
        while (!in.atEnd()) {
            bool ok = false;
            const qint64 t = in.readLine().toLongLong(&ok);
            if (ok && t >= cutoff)
                m_defrostEvents.append(t);
        }
        df.close();
    }

    pruneToFile(m_tempLogPath, cutoff);
    pruneToFile(m_defrostLogPath, cutoff);
}

void HistoryStore::pruneToFile(const QString &path, qint64 cutoff)
{
    // Rewrite the on-disk log to only what survived the cutoff, so the file
    // doesn't grow forever. Cheap enough since this only runs at startup.
    if (path == m_tempLogPath) {
        QFile f(path);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            return;
        QTextStream out(&f);
        for (const TempSample &s : m_tempSamples)
            out << s.t << ';' << s.v << '\n';
    } else {
        QFile f(path);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
            return;
        QTextStream out(&f);
        for (qint64 t : m_defrostEvents)
            out << t << '\n';
    }
}

void HistoryStore::addTempSample(double celsius)
{
    const qint64 now = QDateTime::currentSecsSinceEpoch();
    m_tempSamples.append({ now, celsius });

    QFile f(m_tempLogPath);
    if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&f);
        out << now << ';' << celsius << '\n';
    }
}

void HistoryStore::addDefrostEvent()
{
    const qint64 now = QDateTime::currentSecsSinceEpoch();
    m_defrostEvents.append(now);

    QFile f(m_defrostLogPath);
    if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&f);
        out << now << '\n';
    }
}

QVariantList HistoryStore::temperatureSeries(const QString &range) const
{
    const qint64 cutoff = QDateTime::currentSecsSinceEpoch() - windowSeconds(range);
    QVariantList out;
    for (const TempSample &s : m_tempSamples) {
        if (s.t >= cutoff) {
            QVariantMap m;
            m[QStringLiteral("t")] = s.t;
            m[QStringLiteral("v")] = s.v;
            out.append(m);
        }
    }
    return out;
}

QVariantMap HistoryStore::rangeStats(const QString &range) const
{
    const qint64 cutoff = QDateTime::currentSecsSinceEpoch() - windowSeconds(range);

    double mn = std::numeric_limits<double>::quiet_NaN();
    double mx = std::numeric_limits<double>::quiet_NaN();
    double sum = 0.0;
    int count = 0;
    for (const TempSample &s : m_tempSamples) {
        if (s.t < cutoff)
            continue;
        if (count == 0 || s.v < mn) mn = s.v;
        if (count == 0 || s.v > mx) mx = s.v;
        sum += s.v;
        ++count;
    }

    int defrostCount = 0;
    for (qint64 t : m_defrostEvents)
        if (t >= cutoff)
            ++defrostCount;

    QVariantMap out;
    out[QStringLiteral("count")] = count;
    out[QStringLiteral("min")] = count ? mn : 0.0;
    out[QStringLiteral("max")] = count ? mx : 0.0;
    out[QStringLiteral("avg")] = count ? (sum / count) : 0.0;
    out[QStringLiteral("defrostCount")] = defrostCount;
    return out;
}
