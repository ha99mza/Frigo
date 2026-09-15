#pragma once

#include <QObject>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QString>
#include <QStringList>

// Common interface implemented by both the real CAN transport (CanBackend,
// backed by Qt SerialBus / QCanBus) and the synthetic one (CanSimulator),
// so FrigoController can talk to either without knowing which is active.
class ICanTransport : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    ~ICanTransport() override = default;

    virtual bool connectDevice() = 0;
    virtual void disconnectDevice() = 0;
    virtual bool isConnected() const = 0;
    virtual bool writeFrame(const QCanBusFrame &frame) = 0;

signals:
    void frameReceived(const QCanBusFrame &frame);
    void errorOccurred(const QString &message);
    void connectionStateChanged(bool connected);
};

// Real CAN transport using Qt SerialBus (QCanBus). Plugin/interface are
// resolved at connect time so the same class serves:
//   - Linux:   plugin "socketcan",  interface e.g. "can0", "vcan0"
//   - Windows: plugin "peakcan",    interface e.g. "usb0" (PEAK PCAN-USB)
// Any other QCanBus plugin installed on the system (vectorcan, systeccan,
// tinycan, ...) also works transparently since the QCanBusDevice API is
// identical across backends.
class CanBackend : public ICanTransport
{
    Q_OBJECT
public:
    explicit CanBackend(QObject *parent = nullptr);
    ~CanBackend() override;

    void setPlugin(const QString &pluginName);
    void setInterfaceName(const QString &interfaceName);
    void setBitrate(int bitrate);

    QString plugin() const { return m_pluginName; }
    QString interfaceName() const { return m_interfaceName; }

    // Lists interface names available for a given plugin on this machine
    // (e.g. "can0"/"vcan0" for socketcan, "usb0"/"usb1" for peakcan).
    static QStringList availableInterfaces(const QString &pluginName);
    static QStringList availablePlugins();

    bool connectDevice() override;
    void disconnectDevice() override;
    bool isConnected() const override;
    bool writeFrame(const QCanBusFrame &frame) override;

private slots:
    void onFramesReceived();
    void onDeviceError(QCanBusDevice::CanBusError error);

private:
    QCanBusDevice *m_device = nullptr;
    QString m_pluginName;
    QString m_interfaceName;
    int m_bitrate = 250000;
    bool m_connected = false;
};
