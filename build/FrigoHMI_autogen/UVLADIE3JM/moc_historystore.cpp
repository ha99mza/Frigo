/****************************************************************************
** Meta object code from reading C++ file 'historystore.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/historystore.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'historystore.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12HistoryStoreE_t {};
} // unnamed namespace

template <> constexpr inline auto HistoryStore::qt_create_metaobjectdata<qt_meta_tag_ZN12HistoryStoreE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "HistoryStore",
        "temperatureSeries",
        "QVariantList",
        "",
        "range",
        "rangeStats",
        "QVariantMap",
        "lastDefrostEvent"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'temperatureSeries'
        QtMocHelpers::MethodData<QVariantList(const QString &) const>(1, 3, QMC::AccessPublic, 0x80000000 | 2, {{
            { QMetaType::QString, 4 },
        }}),
        // Method 'rangeStats'
        QtMocHelpers::MethodData<QVariantMap(const QString &) const>(5, 3, QMC::AccessPublic, 0x80000000 | 6, {{
            { QMetaType::QString, 4 },
        }}),
        // Method 'lastDefrostEvent'
        QtMocHelpers::MethodData<qint64() const>(7, 3, QMC::AccessPublic, QMetaType::LongLong),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HistoryStore, qt_meta_tag_ZN12HistoryStoreE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject HistoryStore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12HistoryStoreE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12HistoryStoreE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12HistoryStoreE_t>.metaTypes,
    nullptr
} };

void HistoryStore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HistoryStore *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QVariantList _r = _t->temperatureSeries((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVariantMap _r = _t->rangeStats((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 2: { qint64 _r = _t->lastDefrostEvent();
            if (_a[0]) *reinterpret_cast<qint64*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *HistoryStore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistoryStore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12HistoryStoreE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HistoryStore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
