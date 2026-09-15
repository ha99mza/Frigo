#include "frigocontroller.h"
#include "networkmanager.h"

#include <QCommandLineParser>
#include <QDirIterator>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("Frigo"));
    app.setApplicationName(QStringLiteral("FrigoHMI"));

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Interface tactile frigo (CAN)"));
    parser.addHelpOption();
    QCommandLineOption simulatorOpt(QStringList() << QStringLiteral("simulator"),
        QStringLiteral("Use the built-in CAN simulator instead of real hardware (dev/test)."));
    QCommandLineOption ifaceOpt(QStringList() << QStringLiteral("can-iface"),
        QStringLiteral("CAN interface name (e.g. can0, vcan0, usb0)."), QStringLiteral("name"));
    QCommandLineOption pluginOpt(QStringList() << QStringLiteral("can-plugin"),
        QStringLiteral("QCanBus plugin to use (socketcan, peakcan, vectorcan, ...). Defaults per-platform."), QStringLiteral("plugin"));
    parser.addOption(simulatorOpt);
    parser.addOption(ifaceOpt);
    parser.addOption(pluginOpt);
    parser.process(app);

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE"))
        QQuickStyle::setStyle(QStringLiteral("Basic"));

    QQmlApplicationEngine engine;

    FrigoController frigo;
    engine.rootContext()->setContextProperty(QStringLiteral("frigo"), &frigo);

    NetworkManager netManager;
    engine.rootContext()->setContextProperty(QStringLiteral("netmgr"), &netManager);

    // objectCreationFailed() and loadFromModule() are Qt 6.4/6.5+ only; the
    // target board ships Qt 6.2 (LTS), so fall back to the older equivalents
    // there while still using the nicer API on newer Qt.
#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                      &app, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
#else
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                      &app, [](QObject *obj, const QUrl &) {
                          if (!obj) QCoreApplication::exit(-1);
                      }, Qt::QueuedConnection);
#endif

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    engine.loadFromModule("FrigoHMI", "Main");
#else
    // The internal qrc prefix qt_add_qml_module stages a module's QML files
    // under has changed across Qt versions (see the QTP0001 policy), so
    // rather than hardcode a path that only holds for one version, search
    // the compiled-in resources for Main.qml directly.
    {
        QString mainQmlPath;
        QDirIterator it(QStringLiteral(":/"), QStringList() << QStringLiteral("Main.qml"),
                         QDir::Files, QDirIterator::Subdirectories);
        if (it.hasNext())
            mainQmlPath = it.next();
        if (mainQmlPath.isEmpty()) {
            qFatal("Could not locate Main.qml in the compiled Qt resources");
        }
        engine.load(QUrl(QStringLiteral("qrc") + mainQmlPath));
    }
#endif

    // Auto-connect to the CAN bus — this design has no on-screen connection
    // picker, so the interface is fixed per-platform (or overridden via CLI
    // for dev/test) rather than exposed in the UI.
    if (parser.isSet(simulatorOpt)) {
        frigo.connectSimulator();
    } else {
        QString plugin = parser.value(pluginOpt);
#if defined(FRIGO_PLATFORM_WINDOWS)
        if (plugin.isEmpty()) plugin = QStringLiteral("peakcan");
        const QString iface = parser.isSet(ifaceOpt) ? parser.value(ifaceOpt) : QStringLiteral("usb0");
#else
        if (plugin.isEmpty()) plugin = QStringLiteral("socketcan");
        const QString iface = parser.isSet(ifaceOpt) ? parser.value(ifaceOpt) : QStringLiteral("can0");
#endif
        if (plugin == QStringLiteral("socketcan"))
            frigo.connectSocketCan(iface);
        else
            frigo.connectPeakCan(iface);
    }

    return app.exec();
}
