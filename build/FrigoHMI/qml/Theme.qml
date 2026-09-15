pragma Singleton
import QtQuick
import FrigoHMI 1.0

QtObject {
    // Reads the "Frigo" QML singleton (not the "frigo" context property):
    // pragma-Singleton objects don't reliably see context properties set via
    // QQmlContext::setContextProperty, so the controller is also registered
    // as a proper singleton purely for this to bind against.
    readonly property bool dark: Frigo.darkTheme

    readonly property color bg: dark ? "#12161a" : "#eef1f4"
    readonly property color pn: dark ? "#1b2127" : "#ffffff"
    readonly property color ln: dark ? "#2b333b" : "#d3dae0"
    readonly property color tx: dark ? "#e8edf2" : "#161c22"
    readonly property color mt: dark ? "#93a1ad" : "#5b6873"

    readonly property color accent: "#38bdf8"
    readonly property color red: "#ef4444"
    readonly property color amber: "#f59e0b"
    readonly property color green: "#4ade80"

    readonly property color selBg: dark ? "#0d1f2b" : "#e2f3fd"

    readonly property string sans: "IBM Plex Sans"
    readonly property string mono: "IBM Plex Mono"

    function selColor(on) { return on ? accent : mt }
    function selBgFor(on) { return on ? selBg : "transparent" }
    function selMark(on) { return on ? accent : "transparent" }
}
