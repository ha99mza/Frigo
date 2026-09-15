#pragma once

#include "errorlogmodel.h"
#include "frigoconfig.h"
#include "historystore.h"

#include <QCanBusFrame>
#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QTimer>
#include <memory>

class ICanTransport;

// Root object exposed to QML as `frigo`. Owns the active CAN transport
// (real hardware via CanBackend, or CanSimulator), decodes/encodes the
// protocol, and exposes live sensor state + configuration as properties
// bindable directly from QML.
class FrigoController : public QObject
{
    Q_OBJECT

    // --- Connection -----------------------------------------------------
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QString backendLabel READ backendLabel NOTIFY backendLabelChanged)

    // --- Live sensor state ------------------------------------------------
    Q_PROPERTY(double temp1 READ temp1 NOTIFY temp1Changed)
    Q_PROPERTY(double temp2 READ temp2 NOTIFY temp2Changed)
    Q_PROPERTY(double temp3 READ temp3 NOTIFY temp3Changed)
    Q_PROPERTY(double tempEva READ tempEva NOTIFY tempEvaChanged)
    Q_PROPERTY(double tempAverage READ tempAverage NOTIFY tempAverageChanged)
    Q_PROPERTY(double batteryVoltage READ batteryVoltage NOTIFY batteryVoltageChanged)
    Q_PROPERTY(bool doorOpen READ doorOpen NOTIFY doorOpenChanged)

    Q_PROPERTY(bool fan1On READ fan1On NOTIFY relaysChanged)
    Q_PROPERTY(bool fan2On READ fan2On NOTIFY relaysChanged)
    Q_PROPERTY(bool fan3On READ fan3On NOTIFY relaysChanged)
    Q_PROPERTY(bool fan4On READ fan4On NOTIFY relaysChanged)
    Q_PROPERTY(bool fan5On READ fan5On NOTIFY relaysChanged)
    Q_PROPERTY(bool lampOn READ lampOn NOTIFY relaysChanged)
    Q_PROPERTY(bool compressorOn READ compressorOn NOTIFY relaysChanged)
    Q_PROPERTY(bool defrostFanOn READ defrostFanOn NOTIFY relaysChanged)
    Q_PROPERTY(bool doorRelayOn READ doorRelayOn NOTIFY relaysChanged)

    // --- Configuration (UI units, matching the approved design) -----------
    Q_PROPERTY(double tempMinC READ tempMinC WRITE setTempMinC NOTIFY configChanged)
    Q_PROPERTY(double tempMaxC READ tempMaxC WRITE setTempMaxC NOTIFY configChanged)
    Q_PROPERTY(double tempEvaMinC READ tempEvaMinC WRITE setTempEvaMinC NOTIFY configChanged)
    Q_PROPERTY(double defrostIntervalHours READ defrostIntervalHours WRITE setDefrostIntervalHours NOTIFY configChanged)
    Q_PROPERTY(double defrostDurationMinutes READ defrostDurationMinutes WRITE setDefrostDurationMinutes NOTIFY configChanged)
    Q_PROPERTY(double defrostTimeoutMinutes READ defrostTimeoutMinutes WRITE setDefrostTimeoutMinutes NOTIFY configChanged)
    Q_PROPERTY(double antiShortCycleDelayMinutes READ antiShortCycleDelayMinutes WRITE setAntiShortCycleDelayMinutes NOTIFY configChanged)
    Q_PROPERTY(double tempLimitTimeoutMinutes READ tempLimitTimeoutMinutes WRITE setTempLimitTimeoutMinutes NOTIFY configChanged)
    Q_PROPERTY(double doorAlarmDelaySeconds READ doorAlarmDelaySeconds WRITE setDoorAlarmDelaySeconds NOTIFY configChanged)
    Q_PROPERTY(double offsetCap1C READ offsetCap1C WRITE setOffsetCap1C NOTIFY configChanged)
    Q_PROPERTY(double offsetCap2C READ offsetCap2C WRITE setOffsetCap2C NOTIFY configChanged)
    Q_PROPERTY(double offsetCap3C READ offsetCap3C WRITE setOffsetCap3C NOTIFY configChanged)
    Q_PROPERTY(double offsetEvaC READ offsetEvaC WRITE setOffsetEvaC NOTIFY configChanged)
    Q_PROPERTY(bool maintenanceMode READ maintenanceMode NOTIFY configChanged)

    Q_PROPERTY(bool configDirty READ configDirty NOTIFY configDirtyChanged)
    Q_PROPERTY(bool configSynced READ configSynced NOTIFY configSyncedChanged)
    Q_PROPERTY(int localSignature READ localSignature NOTIFY configChanged)
    Q_PROPERTY(int boardSignature READ boardSignature NOTIFY boardSignatureChanged)

    Q_PROPERTY(ErrorLogModel *errorLog READ errorLog CONSTANT)

    // --- App-local settings (not CAN registers) ---------------------------
    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeChanged)
    Q_PROPERTY(QString unitName READ unitName WRITE setUnitName NOTIFY unitNameChanged)
    Q_PROPERTY(bool settingsUnlocked READ settingsUnlocked NOTIFY settingsUnlockedChanged)

public:
    explicit FrigoController(QObject *parent = nullptr);
    ~FrigoController() override;

    bool connected() const { return m_connected; }
    QString lastError() const { return m_lastError; }
    QString backendLabel() const { return m_backendLabel; }

    double temp1() const { return m_temp1; }
    double temp2() const { return m_temp2; }
    double temp3() const { return m_temp3; }
    double tempEva() const { return m_tempEva; }
    double tempAverage() const;
    double batteryVoltage() const { return m_batteryVoltage; }
    bool doorOpen() const { return m_doorOpen; }

    bool fan1On() const { return m_relayPack1 & 0x01; }
    bool fan2On() const { return m_relayPack1 & 0x02; }
    bool fan3On() const { return m_relayPack1 & 0x04; }
    bool fan4On() const { return m_relayPack1 & 0x08; }
    bool fan5On() const { return m_relayPack1 & 0x10; }
    bool lampOn() const { return m_relayPack2 & 0x01; }
    bool compressorOn() const { return m_relayPack2 & 0x02; }
    bool defrostFanOn() const { return m_relayPack2 & 0x04; }
    bool doorRelayOn() const { return m_relayPack2 & 0x08; }

    double tempMinC() const { return m_config.tempMin / 10.0; }
    double tempMaxC() const { return m_config.tempMax / 10.0; }
    double tempEvaMinC() const { return m_config.tempEvaMin / 10.0; }
    double defrostIntervalHours() const { return m_config.defrostInterval / 3600.0; }
    double defrostDurationMinutes() const { return m_config.defrostDuration / 60.0; }
    double defrostTimeoutMinutes() const { return m_config.defrostTimeout / 60.0; }
    double antiShortCycleDelayMinutes() const { return m_config.antiShortCycleDelay / 60.0; }
    double tempLimitTimeoutMinutes() const { return m_config.tempLimitTimeout / 60.0; }
    double doorAlarmDelaySeconds() const { return m_config.doorAlarmDelay; }
    double offsetCap1C() const { return m_config.offsetCap1 / 10.0; }
    double offsetCap2C() const { return m_config.offsetCap2 / 10.0; }
    double offsetCap3C() const { return m_config.offsetCap3 / 10.0; }
    double offsetEvaC() const { return m_config.offsetEva / 10.0; }
    bool maintenanceMode() const { return m_config.maintenanceMode; }

    void setTempMinC(double v);
    void setTempMaxC(double v);
    void setTempEvaMinC(double v);
    void setDefrostIntervalHours(double v);
    void setDefrostDurationMinutes(double v);
    void setDefrostTimeoutMinutes(double v);
    void setAntiShortCycleDelayMinutes(double v);
    void setTempLimitTimeoutMinutes(double v);
    void setDoorAlarmDelaySeconds(double v);
    void setOffsetCap1C(double v);
    void setOffsetCap2C(double v);
    void setOffsetCap3C(double v);
    void setOffsetEvaC(double v);

    bool configDirty() const { return m_configDirty; }
    bool configSynced() const { return m_configSynced; }
    int localSignature() const { return m_config.computeSignature(); }
    int boardSignature() const { return m_config.boardCommitSignature; }

    ErrorLogModel *errorLog() { return &m_errorLog; }

    bool darkTheme() const { return m_darkTheme; }
    void setDarkTheme(bool v);
    QString unitName() const { return m_unitName; }
    void setUnitName(const QString &v);
    bool settingsUnlocked() const { return m_settingsUnlocked; }

    // --- QML-invokable actions -------------------------------------------
    Q_INVOKABLE void requestConfigFromBoard();
    Q_INVOKABLE void writeConfigToBoard();
    Q_INVOKABLE void verifySignature();

    Q_INVOKABLE void acknowledgeDoorAlarm();
    // Marks every currently-active log entry as cleared; also sends the
    // CAN door-alarm-clear command if a door alarm is among them (that's
    // the only error the protocol lets us actively acknowledge on the bus —
    // the rest simply stop repeating once the underlying fault clears).
    Q_INVOKABLE void acknowledgeAllAlarms();

    // Sent immediately (not part of the dirty/save settings-form flow),
    // since entering/leaving maintenance should take effect right away.
    Q_INVOKABLE void commandMaintenanceMode(bool on);

    // Manual output overrides, meaningful while maintenanceMode is active.
    // index is 0-4 for Fan1-5. key is one of "comp","door","lamp","dfan".
    Q_INVOKABLE void toggleFanOverride(int index);
    Q_INVOKABLE void toggleRelayOverride(const QString &key);

    // PIN gate for the Réglages/Maintenance areas.
    Q_INVOKABLE bool tryUnlockSettings(const QString &pin);
    Q_INVOKABLE void lockSettings();
    // Only allowed while settingsUnlocked (reaching Maintenance already
    // required the current PIN), matching the design's flow.
    Q_INVOKABLE bool changeSettingsPin(const QString &newPin);

    // Historique page data.
    Q_INVOKABLE QVariantList temperatureSeries(const QString &range) const { return m_history.temperatureSeries(range); }
    Q_INVOKABLE QVariantMap rangeStats(const QString &range) const { return m_history.rangeStats(range); }
    Q_INVOKABLE qint64 lastDefrostEvent() const { return m_history.lastDefrostEvent(); }

    // Called once from main.cpp after parsing CLI args.
    void connectSocketCan(const QString &interfaceName);
    void connectPeakCan(const QString &interfaceName);
    void connectSimulator();
    Q_INVOKABLE void disconnectCan();

signals:
    void connectedChanged();
    void lastErrorChanged();
    void backendLabelChanged();

    void temp1Changed();
    void temp2Changed();
    void temp3Changed();
    void tempEvaChanged();
    void tempAverageChanged();
    void batteryVoltageChanged();
    void doorOpenChanged();
    void relaysChanged();

    void configChanged();
    void configDirtyChanged();
    void configSyncedChanged();
    void boardSignatureChanged();

    void darkThemeChanged();
    void unitNameChanged();
    void settingsUnlockedChanged();

    void errorReceived(quint8 code);

private slots:
    void onFrameReceived(const QCanBusFrame &frame);
    void onTransportError(const QString &message);
    void onTransportConnectionChanged(bool connected);
    void onHistoryTick();

private:
    void setTransport(ICanTransport *transport, const QString &label);
    void handleConfigFrame(quint32 id, const QByteArray &payload);
    void requestSignatureDelayed();
    void markConfigDirty();
    void sendRelayMasks();

    std::unique_ptr<ICanTransport> m_transport;
    bool m_connected = false;
    QString m_lastError;
    QString m_backendLabel = QStringLiteral("Déconnecté");

    double m_temp1 = 0.0;
    double m_temp2 = 0.0;
    double m_temp3 = 0.0;
    double m_tempEva = 0.0;
    double m_batteryVoltage = 0.0;
    bool m_doorOpen = false;
    quint8 m_relayPack1 = 0;
    quint8 m_relayPack2 = 0;

    FrigoConfig m_config;
    bool m_configDirty = false;
    bool m_configSynced = false;

    ErrorLogModel m_errorLog;
    QTimer m_signatureCheckTimer;

    QSettings m_settings;
    bool m_darkTheme = true;
    QString m_unitName = QStringLiteral("Chambre froide A2");
    bool m_settingsUnlocked = false;

    HistoryStore m_history;
    QTimer m_historyTimer;
};
