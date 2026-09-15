/****************************************************************************
** Meta object code from reading C++ file 'errorlogmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/errorlogmodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'errorlogmodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13ErrorLogModelE_t {};
} // unnamed namespace

template <> constexpr inline auto ErrorLogModel::qt_create_metaobjectdata<qt_meta_tag_ZN13ErrorLogModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ErrorLogModel",
        "activeCountChanged",
        "",
        "addError",
        "code",
        "clearActive",
        "clearActiveByCode",
        "clearAllActive",
        "clearAll",
        "activeCount",
        "topActiveSummary",
        "Roles",
        "CodeRole",
        "DescriptionRole",
        "TimestampRole",
        "ActiveRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'activeCountChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'addError'
        QtMocHelpers::MethodData<void(quint8)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 4 },
        }}),
        // Method 'clearActive'
        QtMocHelpers::MethodData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'clearActiveByCode'
        QtMocHelpers::MethodData<void(quint8)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 4 },
        }}),
        // Method 'clearAllActive'
        QtMocHelpers::MethodData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'clearAll'
        QtMocHelpers::MethodData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'activeCount'
        QtMocHelpers::PropertyData<int>(9, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'topActiveSummary'
        QtMocHelpers::PropertyData<QString>(10, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Roles'
        QtMocHelpers::EnumData<enum Roles>(11, 11, QMC::EnumFlags{}).add({
            {   12, Roles::CodeRole },
            {   13, Roles::DescriptionRole },
            {   14, Roles::TimestampRole },
            {   15, Roles::ActiveRole },
        }),
    };
    return QtMocHelpers::metaObjectData<ErrorLogModel, qt_meta_tag_ZN13ErrorLogModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ErrorLogModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ErrorLogModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ErrorLogModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13ErrorLogModelE_t>.metaTypes,
    nullptr
} };

void ErrorLogModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ErrorLogModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->activeCountChanged(); break;
        case 1: _t->addError((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1]))); break;
        case 2: _t->clearActive(); break;
        case 3: _t->clearActiveByCode((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1]))); break;
        case 4: _t->clearAllActive(); break;
        case 5: _t->clearAll(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ErrorLogModel::*)()>(_a, &ErrorLogModel::activeCountChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->activeCount(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->topActiveSummary(); break;
        default: break;
        }
    }
}

const QMetaObject *ErrorLogModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ErrorLogModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ErrorLogModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int ErrorLogModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ErrorLogModel::activeCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
