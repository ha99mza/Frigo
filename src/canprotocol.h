#pragma once

#include <QByteArray>
#include <QString>
#include <QtGlobal>

// Wire-level definitions for the fridge controller CAN protocol.
// All multi-byte integers are little-endian, matching the board's encoding.
namespace CanProtocol {

enum CanId : quint32 {
    Id_Error = 0x001,

    Id_TempCap1   = 0x100,
    Id_TempCap2   = 0x101,
    Id_TempCap3   = 0x102,
    Id_TempEva    = 0x103,
    Id_Battery    = 0x104,
    Id_Door       = 0x105,
    Id_RelayPack1 = 0x106,
    Id_RelayPack2 = 0x107,

    Id_CfgTempMin             = 0x300,
    Id_CfgTempMax             = 0x301,
    Id_CfgTempEvaMin          = 0x302,
    Id_CfgDefrostInterval     = 0x303,
    Id_CfgDefrostDuration     = 0x304,
    Id_CfgDefrostTimeout      = 0x305,
    Id_CfgAntiShortCycleDelay = 0x306,
    Id_CfgTempLimitTimeout    = 0x307,
    Id_CfgDoorAlarmDelay      = 0x308,
    Id_CfgOffsetCap1          = 0x309,
    Id_CfgOffsetCap2          = 0x30A,
    Id_CfgOffsetCap3          = 0x30B,
    Id_CfgOffsetEva           = 0x30C,
    Id_CfgRtcTime             = 0x30D,
    Id_CfgMaintenanceMode     = 0x30E,
    Id_CfgCommitSignature     = 0x30F,
};

// Relay Pack 1 bit masks (0x106)
enum RelayPack1Bit : quint8 {
    Relay1_Fan1 = 0x01,
    Relay1_Fan2 = 0x02,
    Relay1_Fan3 = 0x04,
    Relay1_Fan4 = 0x08,
    Relay1_Fan5 = 0x10,
};

// Relay Pack 2 bit masks (0x107)
enum RelayPack2Bit : quint8 {
    Relay2_Lamp        = 0x01,
    Relay2_Compressor  = 0x02,
    Relay2_DefrostFan  = 0x04,
    Relay2_DoorRelay   = 0x08,
};

// Door state (0x105)
enum DoorState : quint8 {
    Door_Closed     = 0x00,
    Door_Open       = 0x03,
    Door_AlarmClear = 0x02, // TX: acknowledge/stop the door-open alarm
};

// System error codes (0x001)
enum ErrorCode : quint8 {
    Err_None = 0x00,

    Err_RtcInit  = 0x11,
    Err_RtcRead  = 0x12,
    Err_RtcWrite = 0x13,

    Err_Sensor1 = 0x21,
    Err_Sensor2 = 0x22,
    Err_Sensor3 = 0x23,
    Err_Sensor4 = 0x24,

    Err_FlashInit  = 0x31,
    Err_FlashRead  = 0x32,
    Err_FlashWrite = 0x33,

    Err_EepromInit  = 0x41,
    Err_EepromRead  = 0x42,
    Err_EepromWrite = 0x43,

    Err_TempLimitTimeout = 0x51,
    Err_DoorTimeout      = 0x52,
    Err_DefrostTimeout   = 0x53,
};

// Human-readable (French) description of an error code, for the UI log.
QString errorCodeToString(quint8 code);

// Whether a given CAN id is one of the 13 "config" registers included in
// the commit-signature checksum (0x300..0x30C).
bool isSignedConfigId(quint32 id);

// --- Little-endian codecs -------------------------------------------------
qint16  decodeInt16LE(const QByteArray &data);
QByteArray encodeInt16LE(qint16 value);

quint16 decodeUInt16LE(const QByteArray &data);
QByteArray encodeUInt16LE(quint16 value);

qint32  decodeInt32LE(const QByteArray &data);
QByteArray encodeInt32LE(qint32 value);

quint32 decodeUInt32LE(const QByteArray &data);
QByteArray encodeUInt32LE(quint32 value);

// --- Physical unit helpers -------------------------------------------------
// Temperatures / offsets are transmitted as raw integers = physical value x 10.
constexpr double rawToTempC(qint32 raw) { return raw / 10.0; }
constexpr qint32 tempCToRaw(double celsius) { return static_cast<qint32>(celsius * 10.0 + (celsius >= 0 ? 0.5 : -0.5)); }

// Battery (0x104) is int16 LE / 1000 (volts).
constexpr double rawToVolts(qint16 raw) { return raw / 1000.0; }

} // namespace CanProtocol
