#include "canprotocol.h"

namespace CanProtocol {

QString errorCodeToString(quint8 code)
{
    switch (code) {
    case Err_None:            return QStringLiteral("Aucune erreur");
    case Err_RtcInit:         return QStringLiteral("Erreur init. RTC");
    case Err_RtcRead:         return QStringLiteral("Erreur lecture RTC");
    case Err_RtcWrite:        return QStringLiteral("Erreur écriture RTC");
    case Err_Sensor1:         return QStringLiteral("Erreur capteur SEN1");
    case Err_Sensor2:         return QStringLiteral("Erreur capteur SEN2");
    case Err_Sensor3:         return QStringLiteral("Erreur capteur SEN3");
    case Err_Sensor4:         return QStringLiteral("Erreur capteur SEN4");
    case Err_FlashInit:       return QStringLiteral("Erreur init. Flash");
    case Err_FlashRead:       return QStringLiteral("Erreur lecture Flash");
    case Err_FlashWrite:      return QStringLiteral("Erreur écriture Flash");
    case Err_EepromInit:      return QStringLiteral("Erreur init. EEPROM");
    case Err_EepromRead:      return QStringLiteral("Erreur lecture EEPROM");
    case Err_EepromWrite:     return QStringLiteral("Erreur écriture EEPROM");
    case Err_TempLimitTimeout:return QStringLiteral("Timeout limite de température");
    case Err_DoorTimeout:     return QStringLiteral("Timeout porte ouverte");
    case Err_DefrostTimeout:  return QStringLiteral("Timeout dégivrage");
    default:
        return QStringLiteral("Erreur inconnue (0x%1)").arg(code, 2, 16, QLatin1Char('0'));
    }
}

bool isSignedConfigId(quint32 id)
{
    return id >= Id_CfgTempMin && id <= Id_CfgOffsetEva;
}

qint16 decodeInt16LE(const QByteArray &data)
{
    if (data.size() < 2)
        return 0;
    quint16 raw = static_cast<quint8>(data[0]) | (static_cast<quint16>(static_cast<quint8>(data[1])) << 8);
    return static_cast<qint16>(raw);
}

QByteArray encodeInt16LE(qint16 value)
{
    QByteArray out(2, Qt::Uninitialized);
    quint16 raw = static_cast<quint16>(value);
    out[0] = static_cast<char>(raw & 0xFF);
    out[1] = static_cast<char>((raw >> 8) & 0xFF);
    return out;
}

quint16 decodeUInt16LE(const QByteArray &data)
{
    if (data.size() < 2)
        return 0;
    return static_cast<quint8>(data[0]) | (static_cast<quint16>(static_cast<quint8>(data[1])) << 8);
}

QByteArray encodeUInt16LE(quint16 value)
{
    QByteArray out(2, Qt::Uninitialized);
    out[0] = static_cast<char>(value & 0xFF);
    out[1] = static_cast<char>((value >> 8) & 0xFF);
    return out;
}

qint32 decodeInt32LE(const QByteArray &data)
{
    if (data.size() < 4)
        return 0;
    quint32 raw = static_cast<quint8>(data[0])
                | (static_cast<quint32>(static_cast<quint8>(data[1])) << 8)
                | (static_cast<quint32>(static_cast<quint8>(data[2])) << 16)
                | (static_cast<quint32>(static_cast<quint8>(data[3])) << 24);
    return static_cast<qint32>(raw);
}

QByteArray encodeInt32LE(qint32 value)
{
    QByteArray out(4, Qt::Uninitialized);
    quint32 raw = static_cast<quint32>(value);
    out[0] = static_cast<char>(raw & 0xFF);
    out[1] = static_cast<char>((raw >> 8) & 0xFF);
    out[2] = static_cast<char>((raw >> 16) & 0xFF);
    out[3] = static_cast<char>((raw >> 24) & 0xFF);
    return out;
}

quint32 decodeUInt32LE(const QByteArray &data)
{
    if (data.size() < 4)
        return 0;
    return static_cast<quint8>(data[0])
         | (static_cast<quint32>(static_cast<quint8>(data[1])) << 8)
         | (static_cast<quint32>(static_cast<quint8>(data[2])) << 16)
         | (static_cast<quint32>(static_cast<quint8>(data[3])) << 24);
}

QByteArray encodeUInt32LE(quint32 value)
{
    QByteArray out(4, Qt::Uninitialized);
    out[0] = static_cast<char>(value & 0xFF);
    out[1] = static_cast<char>((value >> 8) & 0xFF);
    out[2] = static_cast<char>((value >> 16) & 0xFF);
    out[3] = static_cast<char>((value >> 24) & 0xFF);
    return out;
}

} // namespace CanProtocol
