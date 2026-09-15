#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_FrigoHMI_qml_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_TempPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_HistPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_AlarmsPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_SettingsPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_MaintenancePage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_components_NumPad_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_components_TempChart_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_FrigoHMI_qml_components_SettingsRow_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/TempPage.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_TempPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/HistPage.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_HistPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/AlarmsPage.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_AlarmsPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/SettingsPage.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_SettingsPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/MaintenancePage.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_MaintenancePage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/components/NumPad.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_components_NumPad_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/components/TempChart.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_components_TempChart_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/FrigoHMI/qml/components/SettingsRow.qml"), &QmlCacheGeneratedCode::_qt_qml_FrigoHMI_qml_components_SettingsRow_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_FrigoHMI)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_FrigoHMI))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_FrigoHMI)() {
    return 1;
}
