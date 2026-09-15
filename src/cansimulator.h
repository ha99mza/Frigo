#pragma once

#include "canbackend.h"

#include <QHash>
#include <QTimer>

// Synthetic CAN transport used when no real adapter is available (dev/test,
// or the "Simulateur" option in the connection screen). Generates plausible
// sensor frames on a timer and echoes back configuration writes/RTR reads so
// the whole UI (including the settings screen and commit-signature check)
// can be exercised without hardware.
class CanSimulator : public ICanTransport
{
    Q_OBJECT
public:
    explicit CanSimulator(QObject *parent = nullptr);

    bool connectDevice() override;
    void disconnectDevice() override;
    bool isConnected() const override;
    bool writeFrame(const QCanBusFrame &frame) override;

private slots:
    void tick();

private:
    void seedDefaultConfig();
    void emitFrame(quint32 id, const QByteArray &payload);
    void maybeInjectFault();

    bool m_connected = false;
    QTimer m_timer;
    QHash<quint32, QByteArray> m_configStore; // last known value per config CAN id
    quint8 m_relayPack1 = 0;
    quint8 m_relayPack2 = 0;
    quint8 m_door = 0x00;
    int m_tickCount = 0;
    double m_phase = 0.0;
};
