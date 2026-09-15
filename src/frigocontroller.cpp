#include "frigocontroller.h"
#include "canbackend.h"
#include "cansimulator.h"
#include "canprotocol.h"

#include <QtMath>

using namespace CanProtocol;

FrigoController::FrigoController(QObject *parent)
    : QObject(parent)
    , m_settings(QStringLiteral("Frigo"), QStringLiteral("FrigoHMI"))
{
    m_signatureCheckTimer.setSingleShot(true);
    m_signatureCheckTimer.setInterval(300);
    connect(&m_signatureCheckTimer, &QTimer::timeout, this, &FrigoController::verifySignature);

    m_darkTheme = m_settings.value(QStringLiteral("ui/darkTheme"), true).toBool();
    m_unitName = m_settings.value(QStringLiteral("ui/unitName"), m_unitName).toString();

    m_historyTimer.setInterval(60000);
    connect(&m_historyTimer, &QTimer::timeout, this, &FrigoController::onHistoryTick);
    m_historyTimer.start();
}

FrigoController::~FrigoController() = default;

double FrigoController::tempAverage() const
{
    return (m_temp1 + m_temp2 + m_temp3) / 3.0;
}

void FrigoController::onHistoryTick()
{
    if (m_connected)
        m_history.addTempSample(tempAverage());
}

// --- App-local settings --------------------------------------------------

void FrigoController::setDarkTheme(bool v)
{
    if (v == m_darkTheme) return;
    m_darkTheme = v;
    m_settings.setValue(QStringLiteral("ui/darkTheme"), v);
    emit darkThemeChanged();
}

void FrigoController::setUnitName(const QString &v)
{
    if (v == m_unitName) return;
    m_unitName = v;
    m_settings.setValue(QStringLiteral("ui/unitName"), v);
    emit unitNameChanged();
}

bool FrigoController::tryUnlockSettings(const QString &pin)
{
    const QString stored = m_settings.value(QStringLiteral("security/pin"), QStringLiteral("1234")).toString();
    if (pin == stored) {
        m_settingsUnlocked = true;
        emit settingsUnlockedChanged();
        return true;
    }
    return false;
}

void FrigoController::lockSettings()
{
    if (!m_settingsUnlocked) return;
    m_settingsUnlocked = false;
    emit settingsUnlockedChanged();
}

bool FrigoController::changeSettingsPin(const QString &newPin)
{
    if (!m_settingsUnlocked)
        return false;
    if (newPin.length() != 4)
        return false;
    for (const QChar &c : newPin)
        if (!c.isDigit())
            return false;
    m_settings.setValue(QStringLiteral("security/pin"), newPin);
    return true;
}

// --- Config setters ----------------------------------------------------

void FrigoController::markConfigDirty()
{
    if (!m_configDirty) {
        m_configDirty = true;
        emit configDirtyChanged();
    }
    if (m_configSynced) {
        m_configSynced = false;
        emit configSyncedChanged();
    }
    emit configChanged();
}

void FrigoController::setTempMinC(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.tempMin) return;
    m_config.tempMin = raw;
    markConfigDirty();
}

void FrigoController::setTempMaxC(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.tempMax) return;
    m_config.tempMax = raw;
    markConfigDirty();
}

void FrigoController::setTempEvaMinC(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.tempEvaMin) return;
    m_config.tempEvaMin = raw;
    markConfigDirty();
}

void FrigoController::setDefrostIntervalHours(double v)
{
    const quint32 raw = static_cast<quint32>(qRound(v * 3600.0));
    if (raw == m_config.defrostInterval) return;
    m_config.defrostInterval = raw;
    markConfigDirty();
}

void FrigoController::setDefrostDurationMinutes(double v)
{
    const quint32 raw = static_cast<quint32>(qRound(v * 60.0));
    if (raw == m_config.defrostDuration) return;
    m_config.defrostDuration = raw;
    markConfigDirty();
}

void FrigoController::setDefrostTimeoutMinutes(double v)
{
    const quint32 raw = static_cast<quint32>(qRound(v * 60.0));
    if (raw == m_config.defrostTimeout) return;
    m_config.defrostTimeout = raw;
    markConfigDirty();
}

void FrigoController::setAntiShortCycleDelayMinutes(double v)
{
    const quint32 raw = static_cast<quint32>(qRound(v * 60.0));
    if (raw == m_config.antiShortCycleDelay) return;
    m_config.antiShortCycleDelay = raw;
    markConfigDirty();
}

void FrigoController::setTempLimitTimeoutMinutes(double v)
{
    const quint32 raw = static_cast<quint32>(qRound(v * 60.0));
    if (raw == m_config.tempLimitTimeout) return;
    m_config.tempLimitTimeout = raw;
    markConfigDirty();
}

void FrigoController::setDoorAlarmDelaySeconds(double v)
{
    const quint32 raw = static_cast<quint32>(qRound(v));
    if (raw == m_config.doorAlarmDelay) return;
    m_config.doorAlarmDelay = raw;
    markConfigDirty();
}

void FrigoController::setOffsetCap1C(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.offsetCap1) return;
    m_config.offsetCap1 = raw;
    markConfigDirty();
}

void FrigoController::setOffsetCap2C(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.offsetCap2) return;
    m_config.offsetCap2 = raw;
    markConfigDirty();
}

void FrigoController::setOffsetCap3C(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.offsetCap3) return;
    m_config.offsetCap3 = raw;
    markConfigDirty();
}

void FrigoController::setOffsetEvaC(double v)
{
    const qint32 raw = tempCToRaw(v);
    if (raw == m_config.offsetEva) return;
    m_config.offsetEva = raw;
    markConfigDirty();
}

void FrigoController::commandMaintenanceMode(bool on)
{
    m_config.maintenanceMode = on;
    emit configChanged();
    if (!m_transport || !m_connected)
        return;
    m_transport->writeFrame(QCanBusFrame(Id_CfgMaintenanceMode, QByteArray(1, char(on ? 0x01 : 0x00))));
}

// --- Manual overrides (maintenance) ---------------------------------------

void FrigoController::sendRelayMasks()
{
    if (!m_transport || !m_connected)
        return;
    m_transport->writeFrame(QCanBusFrame(Id_RelayPack1, QByteArray(1, char(m_relayPack1))));
    m_transport->writeFrame(QCanBusFrame(Id_RelayPack2, QByteArray(1, char(m_relayPack2))));
}

void FrigoController::toggleFanOverride(int index)
{
    if (index < 0 || index > 4)
        return;
    m_relayPack1 ^= static_cast<quint8>(1u << index);
    emit relaysChanged();
    sendRelayMasks();
}

void FrigoController::toggleRelayOverride(const QString &key)
{
    quint8 bit = 0;
    if (key == QStringLiteral("lamp")) bit = Relay2_Lamp;
    else if (key == QStringLiteral("comp")) bit = Relay2_Compressor;
    else if (key == QStringLiteral("dfan")) bit = Relay2_DefrostFan;
    else if (key == QStringLiteral("door")) bit = Relay2_DoorRelay;
    else return;

    const bool wasDefrostOn = defrostFanOn();
    m_relayPack2 ^= bit;
    emit relaysChanged();
    if (!wasDefrostOn && defrostFanOn())
        m_history.addDefrostEvent();
    sendRelayMasks();
}

// --- Connection management ----------------------------------------------

void FrigoController::setTransport(ICanTransport *transport, const QString &label)
{
    if (m_transport) {
        m_transport->disconnectDevice();
        disconnect(m_transport.get(), nullptr, this, nullptr);
    }
    m_transport.reset(transport);
    m_backendLabel = label;
    emit backendLabelChanged();

    connect(m_transport.get(), &ICanTransport::frameReceived, this, &FrigoController::onFrameReceived);
    connect(m_transport.get(), &ICanTransport::errorOccurred, this, &FrigoController::onTransportError);
    connect(m_transport.get(), &ICanTransport::connectionStateChanged, this, &FrigoController::onTransportConnectionChanged);
}

void FrigoController::connectSocketCan(const QString &interfaceName)
{
    auto *backend = new CanBackend();
    backend->setPlugin(QStringLiteral("socketcan"));
    backend->setInterfaceName(interfaceName);
    setTransport(backend, QStringLiteral("SocketCAN (%1)").arg(interfaceName));
    backend->connectDevice();
}

void FrigoController::connectPeakCan(const QString &interfaceName)
{
    auto *backend = new CanBackend();
    backend->setPlugin(QStringLiteral("peakcan"));
    backend->setInterfaceName(interfaceName);
    setTransport(backend, QStringLiteral("PCAN-USB (%1)").arg(interfaceName));
    backend->connectDevice();
}

void FrigoController::connectSimulator()
{
    auto *sim = new CanSimulator();
    setTransport(sim, QStringLiteral("Simulateur"));
    sim->connectDevice();
}

void FrigoController::disconnectCan()
{
    if (m_transport)
        m_transport->disconnectDevice();
}

void FrigoController::onTransportError(const QString &message)
{
    m_lastError = message;
    emit lastErrorChanged();
}

void FrigoController::onTransportConnectionChanged(bool connected)
{
    if (m_connected == connected)
        return;
    m_connected = connected;
    emit connectedChanged();
    if (connected)
        requestConfigFromBoard();
}

// --- Frame handling --------------------------------------------------------

void FrigoController::onFrameReceived(const QCanBusFrame &frame)
{
    const quint32 id = frame.frameId();
    const QByteArray payload = frame.payload();

    if (id == Id_Error) {
        if (!payload.isEmpty()) {
            const quint8 code = static_cast<quint8>(payload.at(0));
            if (code != Err_None) {
                m_errorLog.addError(code);
                emit errorReceived(code);
            }
        }
        return;
    }

    if (id == Id_TempCap1) {
        m_temp1 = rawToTempC(decodeInt16LE(payload));
        emit temp1Changed();
        emit tempAverageChanged();
        return;
    }
    if (id == Id_TempCap2) {
        m_temp2 = rawToTempC(decodeInt16LE(payload));
        emit temp2Changed();
        emit tempAverageChanged();
        return;
    }
    if (id == Id_TempCap3) {
        m_temp3 = rawToTempC(decodeInt16LE(payload));
        emit temp3Changed();
        emit tempAverageChanged();
        return;
    }
    if (id == Id_TempEva) {
        m_tempEva = rawToTempC(decodeInt16LE(payload));
        emit tempEvaChanged();
        return;
    }
    if (id == Id_Battery) {
        m_batteryVoltage = rawToVolts(decodeInt16LE(payload));
        emit batteryVoltageChanged();
        return;
    }
    if (id == Id_Door) {
        if (!payload.isEmpty()) {
            const quint8 raw = static_cast<quint8>(payload.at(0));
            const bool open = (raw == Door_Open);
            if (open != m_doorOpen) {
                m_doorOpen = open;
                emit doorOpenChanged();
            }
            if (raw == Door_AlarmClear)
                m_errorLog.clearActiveByCode(Err_DoorTimeout);
        }
        return;
    }
    if (id == Id_RelayPack1) {
        if (!payload.isEmpty()) {
            m_relayPack1 = static_cast<quint8>(payload.at(0));
            emit relaysChanged();
        }
        return;
    }
    if (id == Id_RelayPack2) {
        if (!payload.isEmpty()) {
            const bool wasDefrostOn = defrostFanOn();
            m_relayPack2 = static_cast<quint8>(payload.at(0));
            emit relaysChanged();
            if (!wasDefrostOn && defrostFanOn())
                m_history.addDefrostEvent();
        }
        return;
    }
    if (id >= Id_CfgTempMin && id <= Id_CfgCommitSignature) {
        handleConfigFrame(id, payload);
        return;
    }
}

void FrigoController::handleConfigFrame(quint32 id, const QByteArray &payload)
{
    // Signature responses are always processed, even mid-edit; every other
    // config register is ignored while the user has unsaved local changes,
    // so an unrelated board broadcast can't clobber an in-progress edit.
    if (id == Id_CfgCommitSignature) {
        m_config.boardCommitSignature = decodeUInt16LE(payload);
        emit boardSignatureChanged();
        const bool synced = (m_config.boardCommitSignature == m_config.computeSignature());
        if (synced != m_configSynced) {
            m_configSynced = synced;
            emit configSyncedChanged();
        }
        return;
    }

    // Maintenance mode can change on the board (entered/left there, or by us
    // via commandMaintenanceMode) independently of the settings-form dirty
    // state, so always accept it.
    if (id == Id_CfgMaintenanceMode) {
        const bool on = !payload.isEmpty() && payload.at(0) != 0;
        if (on != m_config.maintenanceMode) {
            m_config.maintenanceMode = on;
            emit configChanged();
        }
        return;
    }

    if (m_configDirty)
        return;

    switch (id) {
    case Id_CfgTempMin:             m_config.tempMin = decodeInt32LE(payload); break;
    case Id_CfgTempMax:             m_config.tempMax = decodeInt32LE(payload); break;
    case Id_CfgTempEvaMin:          m_config.tempEvaMin = decodeInt32LE(payload); break;
    case Id_CfgDefrostInterval:     m_config.defrostInterval = decodeUInt32LE(payload); break;
    case Id_CfgDefrostDuration:     m_config.defrostDuration = decodeUInt32LE(payload); break;
    case Id_CfgDefrostTimeout:      m_config.defrostTimeout = decodeUInt32LE(payload); break;
    case Id_CfgAntiShortCycleDelay: m_config.antiShortCycleDelay = decodeUInt32LE(payload); break;
    case Id_CfgTempLimitTimeout:    m_config.tempLimitTimeout = decodeUInt32LE(payload); break;
    case Id_CfgDoorAlarmDelay:      m_config.doorAlarmDelay = decodeUInt32LE(payload); break;
    case Id_CfgOffsetCap1:          m_config.offsetCap1 = decodeInt32LE(payload); break;
    case Id_CfgOffsetCap2:          m_config.offsetCap2 = decodeInt32LE(payload); break;
    case Id_CfgOffsetCap3:          m_config.offsetCap3 = decodeInt32LE(payload); break;
    case Id_CfgOffsetEva:           m_config.offsetEva = decodeInt32LE(payload); break;
    case Id_CfgRtcTime:             m_config.rtcTime = decodeUInt32LE(payload); break;
    default: return;
    }
    emit configChanged();
}

// --- Actions ---------------------------------------------------------------

void FrigoController::requestConfigFromBoard()
{
    if (!m_transport || !m_connected)
        return;

    auto request = [this](quint32 id) {
        QCanBusFrame f(id, QByteArray());
        f.setFrameType(QCanBusFrame::RemoteRequestFrame);
        m_transport->writeFrame(f);
    };

    for (quint32 id : { Id_CfgTempMin, Id_CfgTempMax, Id_CfgTempEvaMin, Id_CfgDefrostInterval,
                         Id_CfgDefrostDuration, Id_CfgDefrostTimeout, Id_CfgAntiShortCycleDelay,
                         Id_CfgTempLimitTimeout, Id_CfgDoorAlarmDelay, Id_CfgOffsetCap1,
                         Id_CfgOffsetCap2, Id_CfgOffsetCap3, Id_CfgOffsetEva, Id_CfgMaintenanceMode }) {
        request(id);
    }
    requestSignatureDelayed();
}

void FrigoController::writeConfigToBoard()
{
    if (!m_transport || !m_connected)
        return;

    auto send = [this](quint32 id, const QByteArray &payload) {
        m_transport->writeFrame(QCanBusFrame(id, payload));
    };

    send(Id_CfgTempMin, encodeInt32LE(m_config.tempMin));
    send(Id_CfgTempMax, encodeInt32LE(m_config.tempMax));
    send(Id_CfgTempEvaMin, encodeInt32LE(m_config.tempEvaMin));
    send(Id_CfgDefrostInterval, encodeUInt32LE(m_config.defrostInterval));
    send(Id_CfgDefrostDuration, encodeUInt32LE(m_config.defrostDuration));
    send(Id_CfgDefrostTimeout, encodeUInt32LE(m_config.defrostTimeout));
    send(Id_CfgAntiShortCycleDelay, encodeUInt32LE(m_config.antiShortCycleDelay));
    send(Id_CfgTempLimitTimeout, encodeUInt32LE(m_config.tempLimitTimeout));
    send(Id_CfgDoorAlarmDelay, encodeUInt32LE(m_config.doorAlarmDelay));
    send(Id_CfgOffsetCap1, encodeInt32LE(m_config.offsetCap1));
    send(Id_CfgOffsetCap2, encodeInt32LE(m_config.offsetCap2));
    send(Id_CfgOffsetCap3, encodeInt32LE(m_config.offsetCap3));
    send(Id_CfgOffsetEva, encodeInt32LE(m_config.offsetEva));

    if (m_configDirty) {
        m_configDirty = false;
        emit configDirtyChanged();
    }
    requestSignatureDelayed();
}

void FrigoController::requestSignatureDelayed()
{
    m_signatureCheckTimer.start();
}

void FrigoController::verifySignature()
{
    if (!m_transport || !m_connected)
        return;
    QCanBusFrame f(Id_CfgCommitSignature, QByteArray());
    f.setFrameType(QCanBusFrame::RemoteRequestFrame);
    m_transport->writeFrame(f);
}

void FrigoController::acknowledgeDoorAlarm()
{
    if (m_transport && m_connected) {
        QCanBusFrame f(Id_Door, QByteArray(1, char(Door_AlarmClear)));
        m_transport->writeFrame(f);
    }
    m_errorLog.clearActiveByCode(Err_DoorTimeout);
}

void FrigoController::acknowledgeAllAlarms()
{
    if (m_transport && m_connected) {
        // Harmless if no door alarm is active — it's the only error the
        // protocol lets us actively acknowledge on the bus.
        QCanBusFrame f(Id_Door, QByteArray(1, char(Door_AlarmClear)));
        m_transport->writeFrame(f);
    }
    m_errorLog.clearAllActive();
}
