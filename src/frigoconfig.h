#pragma once

#include <QtGlobal>
#include <array>

// Holds the 13 configuration registers (0x300..0x30C) that are covered by
// the commit-signature checksum, plus the 3 extra registers (RTC, maintenance
// mode, commit signature) that are not.
//
// Every field stores the *raw* wire value (i.e. already scaled: temperatures
// and offsets are physical-value x 10; durations/timeouts are seconds).
// Conversion to UI-friendly units (hours, minutes, °C) happens at the
// presentation layer (FrigoController / QML), never here.
struct FrigoConfig {
    qint32  tempMin             = 0;   // 0x300, °C x10
    qint32  tempMax             = 0;   // 0x301, °C x10
    qint32  tempEvaMin          = 0;   // 0x302, °C x10
    quint32 defrostInterval     = 0;   // 0x303, seconds (UI: hours)
    quint32 defrostDuration     = 0;   // 0x304, seconds (UI: minutes)
    quint32 defrostTimeout      = 0;   // 0x305, seconds (UI: minutes)
    quint32 antiShortCycleDelay = 0;   // 0x306, seconds
    quint32 tempLimitTimeout    = 0;   // 0x307, seconds
    quint32 doorAlarmDelay      = 0;   // 0x308, seconds (UI: minutes)
    qint32  offsetCap1          = 0;   // 0x309, °C x10
    qint32  offsetCap2          = 0;   // 0x30A, °C x10
    qint32  offsetCap3          = 0;   // 0x30B, °C x10
    qint32  offsetEva           = 0;   // 0x30C, °C x10

    quint32 rtcTime         = 0;       // 0x30D, unix timestamp (not yet active on the board)
    bool    maintenanceMode = false;   // 0x30E

    // Signature as last reported by the board on 0x30F. Compare against
    // computeSignature() to detect a write that didn't take effect.
    quint16 boardCommitSignature = 0;

    // Sum of the 13 registers above (as raw wire int32 values), modulo
    // 0xFFFF, per the board's documented algorithm.
    quint16 computeSignature() const;
};
