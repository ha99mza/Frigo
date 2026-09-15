/****************************************************************************
** Meta object code from reading C++ file 'frigocontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/frigocontroller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frigocontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15FrigoControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto FrigoController::qt_create_metaobjectdata<qt_meta_tag_ZN15FrigoControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FrigoController",
        "connectedChanged",
        "",
        "lastErrorChanged",
        "backendLabelChanged",
        "temp1Changed",
        "temp2Changed",
        "temp3Changed",
        "tempEvaChanged",
        "tempAverageChanged",
        "batteryVoltageChanged",
        "doorOpenChanged",
        "relaysChanged",
        "configChanged",
        "configDirtyChanged",
        "configSyncedChanged",
        "boardSignatureChanged",
        "darkThemeChanged",
        "unitNameChanged",
        "settingsUnlockedChanged",
        "errorReceived",
        "code",
        "onFrameReceived",
        "QCanBusFrame",
        "frame",
        "onTransportError",
        "message",
        "onTransportConnectionChanged",
        "connected",
        "onHistoryTick",
        "processNextQueuedWrite",
        "acknowledgeDoorAlarm",
        "acknowledgeAllAlarms",
        "commandMaintenanceMode",
        "on",
        "toggleFanOverride",
        "index",
        "toggleRelayOverride",
        "key",
        "tryUnlockSettings",
        "pin",
        "lockSettings",
        "changeSettingsPin",
        "newPin",
        "temperatureSeries",
        "QVariantList",
        "range",
        "rangeStats",
        "QVariantMap",
        "lastDefrostEvent",
        "disconnectCan",
        "lastError",
        "backendLabel",
        "temp1",
        "temp2",
        "temp3",
        "tempEva",
        "tempAverage",
        "batteryVoltage",
        "doorOpen",
        "fan1On",
        "fan2On",
        "fan3On",
        "fan4On",
        "fan5On",
        "lampOn",
        "compressorOn",
        "defrostFanOn",
        "doorRelayOn",
        "tempMinC",
        "tempMaxC",
        "tempEvaMinC",
        "defrostIntervalHours",
        "defrostDurationMinutes",
        "defrostTimeoutMinutes",
        "antiShortCycleDelayMinutes",
        "tempLimitTimeoutMinutes",
        "doorAlarmDelaySeconds",
        "offsetCap1C",
        "offsetCap2C",
        "offsetCap3C",
        "offsetEvaC",
        "maintenanceMode",
        "configDirty",
        "configSynced",
        "localSignature",
        "boardSignature",
        "errorLog",
        "ErrorLogModel*",
        "darkTheme",
        "unitName",
        "settingsUnlocked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connectedChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastErrorChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backendLabelChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'temp1Changed'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'temp2Changed'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'temp3Changed'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tempEvaChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tempAverageChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'batteryVoltageChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'doorOpenChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'relaysChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'configChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'configDirtyChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'configSyncedChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'boardSignatureChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'darkThemeChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'unitNameChanged'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'settingsUnlockedChanged'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorReceived'
        QtMocHelpers::SignalData<void(quint8)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 21 },
        }}),
        // Slot 'onFrameReceived'
        QtMocHelpers::SlotData<void(const QCanBusFrame &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 23, 24 },
        }}),
        // Slot 'onTransportError'
        QtMocHelpers::SlotData<void(const QString &)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'onTransportConnectionChanged'
        QtMocHelpers::SlotData<void(bool)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 28 },
        }}),
        // Slot 'onHistoryTick'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'processNextQueuedWrite'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'acknowledgeDoorAlarm'
        QtMocHelpers::MethodData<void()>(31, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'acknowledgeAllAlarms'
        QtMocHelpers::MethodData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'commandMaintenanceMode'
        QtMocHelpers::MethodData<void(bool)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Method 'toggleFanOverride'
        QtMocHelpers::MethodData<void(int)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 36 },
        }}),
        // Method 'toggleRelayOverride'
        QtMocHelpers::MethodData<void(const QString &)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Method 'tryUnlockSettings'
        QtMocHelpers::MethodData<bool(const QString &)>(39, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 40 },
        }}),
        // Method 'lockSettings'
        QtMocHelpers::MethodData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'changeSettingsPin'
        QtMocHelpers::MethodData<bool(const QString &)>(42, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 43 },
        }}),
        // Method 'temperatureSeries'
        QtMocHelpers::MethodData<QVariantList(const QString &) const>(44, 2, QMC::AccessPublic, 0x80000000 | 45, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'rangeStats'
        QtMocHelpers::MethodData<QVariantMap(const QString &) const>(47, 2, QMC::AccessPublic, 0x80000000 | 48, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'lastDefrostEvent'
        QtMocHelpers::MethodData<qint64() const>(49, 2, QMC::AccessPublic, QMetaType::LongLong),
        // Method 'disconnectCan'
        QtMocHelpers::MethodData<void()>(50, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'connected'
        QtMocHelpers::PropertyData<bool>(28, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'lastError'
        QtMocHelpers::PropertyData<QString>(51, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'backendLabel'
        QtMocHelpers::PropertyData<QString>(52, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'temp1'
        QtMocHelpers::PropertyData<double>(53, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'temp2'
        QtMocHelpers::PropertyData<double>(54, QMetaType::Double, QMC::DefaultPropertyFlags, 4),
        // property 'temp3'
        QtMocHelpers::PropertyData<double>(55, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'tempEva'
        QtMocHelpers::PropertyData<double>(56, QMetaType::Double, QMC::DefaultPropertyFlags, 6),
        // property 'tempAverage'
        QtMocHelpers::PropertyData<double>(57, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'batteryVoltage'
        QtMocHelpers::PropertyData<double>(58, QMetaType::Double, QMC::DefaultPropertyFlags, 8),
        // property 'doorOpen'
        QtMocHelpers::PropertyData<bool>(59, QMetaType::Bool, QMC::DefaultPropertyFlags, 9),
        // property 'fan1On'
        QtMocHelpers::PropertyData<bool>(60, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'fan2On'
        QtMocHelpers::PropertyData<bool>(61, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'fan3On'
        QtMocHelpers::PropertyData<bool>(62, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'fan4On'
        QtMocHelpers::PropertyData<bool>(63, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'fan5On'
        QtMocHelpers::PropertyData<bool>(64, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'lampOn'
        QtMocHelpers::PropertyData<bool>(65, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'compressorOn'
        QtMocHelpers::PropertyData<bool>(66, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'defrostFanOn'
        QtMocHelpers::PropertyData<bool>(67, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'doorRelayOn'
        QtMocHelpers::PropertyData<bool>(68, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'tempMinC'
        QtMocHelpers::PropertyData<double>(69, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'tempMaxC'
        QtMocHelpers::PropertyData<double>(70, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'tempEvaMinC'
        QtMocHelpers::PropertyData<double>(71, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'defrostIntervalHours'
        QtMocHelpers::PropertyData<double>(72, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'defrostDurationMinutes'
        QtMocHelpers::PropertyData<double>(73, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'defrostTimeoutMinutes'
        QtMocHelpers::PropertyData<double>(74, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'antiShortCycleDelayMinutes'
        QtMocHelpers::PropertyData<double>(75, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'tempLimitTimeoutMinutes'
        QtMocHelpers::PropertyData<double>(76, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'doorAlarmDelaySeconds'
        QtMocHelpers::PropertyData<double>(77, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'offsetCap1C'
        QtMocHelpers::PropertyData<double>(78, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'offsetCap2C'
        QtMocHelpers::PropertyData<double>(79, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'offsetCap3C'
        QtMocHelpers::PropertyData<double>(80, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'offsetEvaC'
        QtMocHelpers::PropertyData<double>(81, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'maintenanceMode'
        QtMocHelpers::PropertyData<bool>(82, QMetaType::Bool, QMC::DefaultPropertyFlags, 11),
        // property 'configDirty'
        QtMocHelpers::PropertyData<bool>(83, QMetaType::Bool, QMC::DefaultPropertyFlags, 12),
        // property 'configSynced'
        QtMocHelpers::PropertyData<bool>(84, QMetaType::Bool, QMC::DefaultPropertyFlags, 13),
        // property 'localSignature'
        QtMocHelpers::PropertyData<int>(85, QMetaType::Int, QMC::DefaultPropertyFlags, 11),
        // property 'boardSignature'
        QtMocHelpers::PropertyData<int>(86, QMetaType::Int, QMC::DefaultPropertyFlags, 14),
        // property 'errorLog'
        QtMocHelpers::PropertyData<ErrorLogModel*>(87, 0x80000000 | 88, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'darkTheme'
        QtMocHelpers::PropertyData<bool>(89, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'unitName'
        QtMocHelpers::PropertyData<QString>(90, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'settingsUnlocked'
        QtMocHelpers::PropertyData<bool>(91, QMetaType::Bool, QMC::DefaultPropertyFlags, 17),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<FrigoController, qt_meta_tag_ZN15FrigoControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject FrigoController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15FrigoControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15FrigoControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15FrigoControllerE_t>.metaTypes,
    nullptr
} };

void FrigoController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FrigoController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connectedChanged(); break;
        case 1: _t->lastErrorChanged(); break;
        case 2: _t->backendLabelChanged(); break;
        case 3: _t->temp1Changed(); break;
        case 4: _t->temp2Changed(); break;
        case 5: _t->temp3Changed(); break;
        case 6: _t->tempEvaChanged(); break;
        case 7: _t->tempAverageChanged(); break;
        case 8: _t->batteryVoltageChanged(); break;
        case 9: _t->doorOpenChanged(); break;
        case 10: _t->relaysChanged(); break;
        case 11: _t->configChanged(); break;
        case 12: _t->configDirtyChanged(); break;
        case 13: _t->configSyncedChanged(); break;
        case 14: _t->boardSignatureChanged(); break;
        case 15: _t->darkThemeChanged(); break;
        case 16: _t->unitNameChanged(); break;
        case 17: _t->settingsUnlockedChanged(); break;
        case 18: _t->errorReceived((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1]))); break;
        case 19: _t->onFrameReceived((*reinterpret_cast<std::add_pointer_t<QCanBusFrame>>(_a[1]))); break;
        case 20: _t->onTransportError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->onTransportConnectionChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->onHistoryTick(); break;
        case 23: _t->processNextQueuedWrite(); break;
        case 24: _t->acknowledgeDoorAlarm(); break;
        case 25: _t->acknowledgeAllAlarms(); break;
        case 26: _t->commandMaintenanceMode((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 27: _t->toggleFanOverride((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->toggleRelayOverride((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 29: { bool _r = _t->tryUnlockSettings((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->lockSettings(); break;
        case 31: { bool _r = _t->changeSettingsPin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 32: { QVariantList _r = _t->temperatureSeries((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 33: { QVariantMap _r = _t->rangeStats((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 34: { qint64 _r = _t->lastDefrostEvent();
            if (_a[0]) *reinterpret_cast<qint64*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->disconnectCan(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::connectedChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::lastErrorChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::backendLabelChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::temp1Changed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::temp2Changed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::temp3Changed, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::tempEvaChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::tempAverageChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::batteryVoltageChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::doorOpenChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::relaysChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::configChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::configDirtyChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::configSyncedChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::boardSignatureChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::darkThemeChanged, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::unitNameChanged, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)()>(_a, &FrigoController::settingsUnlockedChanged, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (FrigoController::*)(quint8 )>(_a, &FrigoController::errorReceived, 18))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 37:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ErrorLogModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->connected(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->lastError(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->backendLabel(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->temp1(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->temp2(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->temp3(); break;
        case 6: *reinterpret_cast<double*>(_v) = _t->tempEva(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->tempAverage(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->batteryVoltage(); break;
        case 9: *reinterpret_cast<bool*>(_v) = _t->doorOpen(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->fan1On(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->fan2On(); break;
        case 12: *reinterpret_cast<bool*>(_v) = _t->fan3On(); break;
        case 13: *reinterpret_cast<bool*>(_v) = _t->fan4On(); break;
        case 14: *reinterpret_cast<bool*>(_v) = _t->fan5On(); break;
        case 15: *reinterpret_cast<bool*>(_v) = _t->lampOn(); break;
        case 16: *reinterpret_cast<bool*>(_v) = _t->compressorOn(); break;
        case 17: *reinterpret_cast<bool*>(_v) = _t->defrostFanOn(); break;
        case 18: *reinterpret_cast<bool*>(_v) = _t->doorRelayOn(); break;
        case 19: *reinterpret_cast<double*>(_v) = _t->tempMinC(); break;
        case 20: *reinterpret_cast<double*>(_v) = _t->tempMaxC(); break;
        case 21: *reinterpret_cast<double*>(_v) = _t->tempEvaMinC(); break;
        case 22: *reinterpret_cast<double*>(_v) = _t->defrostIntervalHours(); break;
        case 23: *reinterpret_cast<double*>(_v) = _t->defrostDurationMinutes(); break;
        case 24: *reinterpret_cast<double*>(_v) = _t->defrostTimeoutMinutes(); break;
        case 25: *reinterpret_cast<double*>(_v) = _t->antiShortCycleDelayMinutes(); break;
        case 26: *reinterpret_cast<double*>(_v) = _t->tempLimitTimeoutMinutes(); break;
        case 27: *reinterpret_cast<double*>(_v) = _t->doorAlarmDelaySeconds(); break;
        case 28: *reinterpret_cast<double*>(_v) = _t->offsetCap1C(); break;
        case 29: *reinterpret_cast<double*>(_v) = _t->offsetCap2C(); break;
        case 30: *reinterpret_cast<double*>(_v) = _t->offsetCap3C(); break;
        case 31: *reinterpret_cast<double*>(_v) = _t->offsetEvaC(); break;
        case 32: *reinterpret_cast<bool*>(_v) = _t->maintenanceMode(); break;
        case 33: *reinterpret_cast<bool*>(_v) = _t->configDirty(); break;
        case 34: *reinterpret_cast<bool*>(_v) = _t->configSynced(); break;
        case 35: *reinterpret_cast<int*>(_v) = _t->localSignature(); break;
        case 36: *reinterpret_cast<int*>(_v) = _t->boardSignature(); break;
        case 37: *reinterpret_cast<ErrorLogModel**>(_v) = _t->errorLog(); break;
        case 38: *reinterpret_cast<bool*>(_v) = _t->darkTheme(); break;
        case 39: *reinterpret_cast<QString*>(_v) = _t->unitName(); break;
        case 40: *reinterpret_cast<bool*>(_v) = _t->settingsUnlocked(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 19: _t->setTempMinC(*reinterpret_cast<double*>(_v)); break;
        case 20: _t->setTempMaxC(*reinterpret_cast<double*>(_v)); break;
        case 21: _t->setTempEvaMinC(*reinterpret_cast<double*>(_v)); break;
        case 22: _t->setDefrostIntervalHours(*reinterpret_cast<double*>(_v)); break;
        case 23: _t->setDefrostDurationMinutes(*reinterpret_cast<double*>(_v)); break;
        case 24: _t->setDefrostTimeoutMinutes(*reinterpret_cast<double*>(_v)); break;
        case 25: _t->setAntiShortCycleDelayMinutes(*reinterpret_cast<double*>(_v)); break;
        case 26: _t->setTempLimitTimeoutMinutes(*reinterpret_cast<double*>(_v)); break;
        case 27: _t->setDoorAlarmDelaySeconds(*reinterpret_cast<double*>(_v)); break;
        case 28: _t->setOffsetCap1C(*reinterpret_cast<double*>(_v)); break;
        case 29: _t->setOffsetCap2C(*reinterpret_cast<double*>(_v)); break;
        case 30: _t->setOffsetCap3C(*reinterpret_cast<double*>(_v)); break;
        case 31: _t->setOffsetEvaC(*reinterpret_cast<double*>(_v)); break;
        case 38: _t->setDarkTheme(*reinterpret_cast<bool*>(_v)); break;
        case 39: _t->setUnitName(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *FrigoController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrigoController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15FrigoControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FrigoController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 36;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void FrigoController::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FrigoController::lastErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FrigoController::backendLabelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FrigoController::temp1Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FrigoController::temp2Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void FrigoController::temp3Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void FrigoController::tempEvaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void FrigoController::tempAverageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void FrigoController::batteryVoltageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void FrigoController::doorOpenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void FrigoController::relaysChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void FrigoController::configChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void FrigoController::configDirtyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void FrigoController::configSyncedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void FrigoController::boardSignatureChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void FrigoController::darkThemeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void FrigoController::unitNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void FrigoController::settingsUnlockedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void FrigoController::errorReceived(quint8 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 18, nullptr, _t1);
}
QT_WARNING_POP
