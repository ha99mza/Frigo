#include "canbackend.h"

#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QVariant>

CanBackend::CanBackend(QObject *parent)
    : ICanTransport(parent)
{
#if defined(FRIGO_PLATFORM_WINDOWS)
    m_pluginName = QStringLiteral("peakcan");
    m_interfaceName = QStringLiteral("usb0");
#else
    m_pluginName = QStringLiteral("socketcan");
    m_interfaceName = QStringLiteral("can0");
#endif
}

CanBackend::~CanBackend()
{
    disconnectDevice();
}

void CanBackend::setPlugin(const QString &pluginName)
{
    m_pluginName = pluginName;
}

void CanBackend::setInterfaceName(const QString &interfaceName)
{
    m_interfaceName = interfaceName;
}

void CanBackend::setBitrate(int bitrate)
{
    m_bitrate = bitrate;
}

QStringList CanBackend::availablePlugins()
{
    return QCanBus::instance()->plugins();
}

QStringList CanBackend::availableInterfaces(const QString &pluginName)
{
    QStringList names;
    QString errorString;
    const auto infos = QCanBus::instance()->availableDevices(pluginName, &errorString);
    for (const QCanBusDeviceInfo &info : infos)
        names << info.name();
    return names;
}

bool CanBackend::connectDevice()
{
    if (m_device)
        disconnectDevice();

    QString errorString;
    m_device = QCanBus::instance()->createDevice(m_pluginName, m_interfaceName, &errorString);
    if (!m_device) {
        emit errorOccurred(QStringLiteral("Impossible d'ouvrir %1/%2 : %3")
                                .arg(m_pluginName, m_interfaceName, errorString));
        return false;
    }

    m_device->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant(m_bitrate));

    connect(m_device, &QCanBusDevice::framesReceived, this, &CanBackend::onFramesReceived);
    connect(m_device, &QCanBusDevice::errorOccurred, this, &CanBackend::onDeviceError);

    if (!m_device->connectDevice()) {
        emit errorOccurred(QStringLiteral("Échec de connexion : %1").arg(m_device->errorString()));
        delete m_device;
        m_device = nullptr;
        return false;
    }

    m_connected = true;
    emit connectionStateChanged(true);
    return true;
}

void CanBackend::disconnectDevice()
{
    if (!m_device)
        return;

    m_device->disconnectDevice();
    m_device->deleteLater();
    m_device = nullptr;

    if (m_connected) {
        m_connected = false;
        emit connectionStateChanged(false);
    }
}

bool CanBackend::isConnected() const
{
    return m_connected;
}

bool CanBackend::writeFrame(const QCanBusFrame &frame)
{
    if (!m_device || !m_connected)
        return false;
    return m_device->writeFrame(frame);
}

void CanBackend::onFramesReceived()
{
    if (!m_device)
        return;
    while (m_device->framesAvailable() > 0)
        emit frameReceived(m_device->readFrame());
}

void CanBackend::onDeviceError(QCanBusDevice::CanBusError error)
{
    if (error == QCanBusDevice::NoError || !m_device)
        return;
    emit errorOccurred(m_device->errorString());
}
