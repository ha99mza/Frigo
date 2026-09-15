#include "frigoconfig.h"

#include <array>

quint16 FrigoConfig::computeSignature() const
{
    const std::array<qint32, 13> values = {
        tempMin, tempMax, tempEvaMin,
        static_cast<qint32>(defrostInterval),
        static_cast<qint32>(defrostDuration),
        static_cast<qint32>(defrostTimeout),
        static_cast<qint32>(antiShortCycleDelay),
        static_cast<qint32>(tempLimitTimeout),
        static_cast<qint32>(doorAlarmDelay),
        offsetCap1, offsetCap2, offsetCap3, offsetEva,
    };

    qint64 sum = 0;
    for (qint32 v : values)
        sum += v;

    qint64 mod = sum % 0xFFFF;
    if (mod < 0)
        mod += 0xFFFF;
    return static_cast<quint16>(mod);
}
