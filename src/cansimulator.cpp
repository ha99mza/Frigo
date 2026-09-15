#include "cansimulator.h"
#include "canprotocol.h"
#include "frigoconfig.h"

#include <QRandomGenerator>
#include <QtMath>

using namespace CanProtocol;

CanSimulator::CanSimulator(QObject *parent)
    : ICanTransport(parent)
{
    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &CanSimulator::tick);
    seedDefaultConfig();
}

void CanSimulator::seedDefaultConfig()
{
    m_configStore[Id_CfgTempMin]             = encodeInt32LE(tempCToRaw(2.0));
    m_configStore[Id_CfgTempMax]             = encodeInt32LE(tempCToRaw(8.0));
    m_configStore[Id_CfgTempEvaMin]          = encodeInt32LE(tempCToRaw(-15.0));
    m_configStore[Id_CfgDefrostInterval]     = encodeUInt32LE(6u * 3600u);   // 6 h
    m_configStore[Id_CfgDefrostDuration]     = encodeUInt32LE(20u * 60u);    // 20 min
    m_configStore[Id_CfgDefrostTimeout]      = encodeUInt32LE(45u * 60u);    // 45 min
    m_configStore[Id_CfgAntiShortCycleDelay] = encodeUInt32LE(180u);         // 3 min
    m_configStore[Id_CfgTempLimitTimeout]    = encodeUInt32LE(30u * 60u);    // 30 min
    m_configStore[Id_CfgDoorAlarmDelay]      = encodeUInt32LE(2u * 60u);     // 2 min
    m_configStore[Id_CfgOffsetCap1]          = encodeInt32LE(0);
    m_configStore[Id_CfgOffsetCap2]          = encodeInt32LE(0);
    m_configStore[Id_CfgOffsetCap3]          = encodeInt32LE(0);
    m_configStore[Id_CfgOffsetEva]           = encodeInt32LE(0);
    m_configStore[Id_CfgRtcTime]             = encodeUInt32LE(0);
    m_configStore[Id_CfgMaintenanceMode]     = QByteArray(1, char(0x00));

    m_relayPack2 = Relay2_Compressor; // start with compressor running
}

bool CanSimulator::connectDevice()
{
    m_connected = true;
    m_tickCount = 0;
    m_timer.start();
    emit connectionStateChanged(true);
    return true;
}

void CanSimulator::disconnectDevice()
{
    if (!m_connected)
        return;
    m_timer.stop();
    m_connected = false;
    emit connectionStateChanged(false);
}

bool CanSimulator::isConnected() const
{
    return m_connected;
}

void CanSimulator::emitFrame(quint32 id, const QByteArray &payload)
{
    QCanBusFrame frame(id, payload);
    frame.setExtendedFrameFormat(false);
    emit frameReceived(frame);
}

bool CanSimulator::writeFrame(const QCanBusFrame &frame)
{
    if (!m_connected)
        return false;

    const quint32 id = frame.frameId();

    // RTR (remote transmission request): reply with the stored value.
    if (frame.frameType() == QCanBusFrame::RemoteRequestFrame) {
        if (id == Id_CfgCommitSignature) {
            FrigoConfig cfg;
            cfg.tempMin             = decodeInt32LE(m_configStore[Id_CfgTempMin]);
            cfg.tempMax             = decodeInt32LE(m_configStore[Id_CfgTempMax]);
            cfg.tempEvaMin          = decodeInt32LE(m_configStore[Id_CfgTempEvaMin]);
            cfg.defrostInterval     = decodeUInt32LE(m_configStore[Id_CfgDefrostInterval]);
            cfg.defrostDuration     = decodeUInt32LE(m_configStore[Id_CfgDefrostDuration]);
            cfg.defrostTimeout      = decodeUInt32LE(m_configStore[Id_CfgDefrostTimeout]);
            cfg.antiShortCycleDelay = decodeUInt32LE(m_configStore[Id_CfgAntiShortCycleDelay]);
            cfg.tempLimitTimeout    = decodeUInt32LE(m_configStore[Id_CfgTempLimitTimeout]);
            cfg.doorAlarmDelay      = decodeUInt32LE(m_configStore[Id_CfgDoorAlarmDelay]);
            cfg.offsetCap1          = decodeInt32LE(m_configStore[Id_CfgOffsetCap1]);
            cfg.offsetCap2          = decodeInt32LE(m_configStore[Id_CfgOffsetCap2]);
            cfg.offsetCap3          = decodeInt32LE(m_configStore[Id_CfgOffsetCap3]);
            cfg.offsetEva           = decodeInt32LE(m_configStore[Id_CfgOffsetEva]);
            emitFrame(Id_CfgCommitSignature, encodeUInt16LE(cfg.computeSignature()));
        } else if (m_configStore.contains(id)) {
            emitFrame(id, m_configStore.value(id));
        }
        return true;
    }

    // Normal write: store it and echo back so the UI can confirm the value stuck.
    if (m_configStore.contains(id)) {
        m_configStore[id] = frame.payload();
        emitFrame(id, frame.payload());
        return true;
    }

    if (id == Id_RelayPack1 && frame.payload().size() >= 1) {
        m_relayPack1 = static_cast<quint8>(frame.payload().at(0));
        emitFrame(Id_RelayPack1, frame.payload());
        return true;
    }
    if (id == Id_RelayPack2 && frame.payload().size() >= 1) {
        m_relayPack2 = static_cast<quint8>(frame.payload().at(0));
        emitFrame(Id_RelayPack2, frame.payload());
        return true;
    }
    if (id == Id_Door && frame.payload().size() >= 1) {
        const quint8 cmd = static_cast<quint8>(frame.payload().at(0));
        if (cmd == Door_AlarmClear) {
            // Acknowledge: stop reporting the door-open alarm condition.
            emitFrame(Id_Door, QByteArray(1, char(m_door)));
        }
        return true;
    }

    return false;
}

void CanSimulator::maybeInjectFault()
{
    // Rare, purely for exercising the error log UI in simulator mode.
    if (QRandomGenerator::global()->bounded(600) == 0) {
        static const quint8 demoErrors[] = {
            Err_Sensor2, Err_DoorTimeout, Err_DefrostTimeout, Err_TempLimitTimeout,
        };
        const quint8 code = demoErrors[QRandomGenerator::global()->bounded(4)];
        emitFrame(Id_Error, QByteArray(1, char(code)));
    }
}

void CanSimulator::tick()
{
    ++m_tickCount;
    m_phase += 0.05;

    const double base1 = 4.0 + 1.5 * qSin(m_phase);
    const double base2 = 4.2 + 1.3 * qSin(m_phase + 0.4);
    const double base3 = 3.8 + 1.4 * qSin(m_phase + 0.8);
    const double eva   = -18.0 + 2.0 * qSin(m_phase * 0.7);

    auto noise = [] { return (QRandomGenerator::global()->bounded(21) - 10) / 100.0; };
    emitFrame(Id_TempCap1, encodeInt16LE(static_cast<qint16>(tempCToRaw(base1 + noise()))));
    emitFrame(Id_TempCap2, encodeInt16LE(static_cast<qint16>(tempCToRaw(base2 + noise()))));
    emitFrame(Id_TempCap3, encodeInt16LE(static_cast<qint16>(tempCToRaw(base3 + noise()))));
    emitFrame(Id_TempEva,  encodeInt16LE(static_cast<qint16>(tempCToRaw(eva + noise()))));

    const double volts = 13.6 + 0.2 * qSin(m_phase * 0.3);
    emitFrame(Id_Battery, encodeInt16LE(static_cast<qint16>(volts * 1000)));

    // Simple thermostat: compressor on above tempMax, off below tempMin.
    const double avg = (base1 + base2 + base3) / 3.0;
    const qint32 tMin = decodeInt32LE(m_configStore[Id_CfgTempMin]);
    const qint32 tMax = decodeInt32LE(m_configStore[Id_CfgTempMax]);
    if (tempCToRaw(avg) >= tMax)
        m_relayPack2 |= Relay2_Compressor;
    else if (tempCToRaw(avg) <= tMin)
        m_relayPack2 &= ~Relay2_Compressor;

    if (m_relayPack2 & Relay2_Compressor)
        m_relayPack1 |= (Relay1_Fan1 | Relay1_Fan2);
    else
        m_relayPack1 &= ~(Relay1_Fan1 | Relay1_Fan2);

    if (m_tickCount % 4 == 0) {
        emitFrame(Id_RelayPack1, QByteArray(1, char(m_relayPack1)));
        emitFrame(Id_RelayPack2, QByteArray(1, char(m_relayPack2)));
        emitFrame(Id_Door, QByteArray(1, char(m_door)));
    }

    maybeInjectFault();
}
