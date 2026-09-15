#pragma once

#include <QObject>
#include <QString>
#include <QTimer>

// Thin Linux-only Wi-Fi status/control wrapper around `nmcli` (NetworkManager's
// CLI), polled periodically. Deliberately simple (QProcess + text parsing,
// not the D-Bus API) since nmcli is stable, always present alongside
// NetworkManager, and easy to reason about for an embedded touch UI.
//
// On a system without NetworkManager/nmcli (or on Windows, where it never
// exists), `available` stays false and everything else reports harmless
// empty/false defaults — the Réseau screen falls back to showing that state.
class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available NOTIFY availableChanged)
    Q_PROPERTY(bool wifiEnabled READ wifiEnabled NOTIFY statusChanged)
    Q_PROPERTY(bool wifiConnected READ wifiConnected NOTIFY statusChanged)
    Q_PROPERTY(QString ssid READ ssid NOTIFY statusChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress NOTIFY statusChanged)
    Q_PROPERTY(QString gateway READ gateway NOTIFY statusChanged)
    Q_PROPERTY(QString subnetMask READ subnetMask NOTIFY statusChanged)
    Q_PROPERTY(QString macAddress READ macAddress NOTIFY statusChanged)
    Q_PROPERTY(int signalStrength READ signalStrength NOTIFY statusChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:
    explicit NetworkManager(QObject *parent = nullptr);

    bool available() const { return m_available; }
    bool wifiEnabled() const { return m_wifiEnabled; }
    bool wifiConnected() const { return m_wifiConnected; }
    QString ssid() const { return m_ssid; }
    QString ipAddress() const { return m_ip; }
    QString gateway() const { return m_gateway; }
    QString subnetMask() const { return m_mask; }
    QString macAddress() const { return m_mac; }
    int signalStrength() const { return m_signal; }
    bool busy() const { return m_busy; }

    Q_INVOKABLE void setWifiEnabled(bool on);
    Q_INVOKABLE void rescan();
    Q_INVOKABLE void renewIp();
    Q_INVOKABLE void refresh();

signals:
    void availableChanged();
    void statusChanged();
    void busyChanged();

private:
    void setBusy(bool b);
    void applyStatus();

    QTimer m_pollTimer;
    bool m_available = false;
    bool m_busy = false;

    bool m_wifiEnabled = false;
    bool m_wifiConnected = false;
    QString m_ssid;
    QString m_ip;
    QString m_gateway;
    QString m_mask;
    QString m_mac;
    int m_signal = 0;

    QString m_wifiDevice;       // e.g. "wlan0"
    QString m_activeConnName;   // nmcli connection profile name, for renewIp()
};
