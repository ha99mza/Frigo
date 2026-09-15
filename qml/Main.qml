import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "components"

ApplicationWindow {
    id: window
    width: 1024
    height: 600
    visible: true
    title: "Frigo HMI"
    color: theme.bg

    // Exposed as `Window.window.theme` so every page/component — regardless
    // of which .qml file it lives in — can read the palette the same way,
    // via the standard cross-file "find my window" attached property. (A
    // pragma-Singleton theme.qml was tried first but singletons don't
    // reliably see context properties or self-import their own module, so
    // this ordinary QtObject-on-the-window approach replaced it.)
    readonly property alias theme: theme
    QtObject {
        id: theme
        readonly property bool dark: frigo.darkTheme

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

    property string page: "temp"
    property bool showPin: false
    property string pin: ""
    property string pinErr: ""

    readonly property int activeAlarms: frigo.errorLog.activeCount
    readonly property bool hasAlarm: activeAlarms > 0

    function go(p) {
        if (p === "set" && !frigo.settingsUnlocked) {
            showPin = true; pin = ""; pinErr = "";
            return;
        }
        page = p;
    }

    function pinPress(k) {
        if (k === "del") { pin = pin.slice(0, -1); pinErr = ""; return; }
        if (k === "ok") return;
        if (pin.length >= 4) return;
        pin += k;
        if (pin.length === 4) {
            if (frigo.tryUnlockSettings(pin)) {
                pin = ""; showPin = false; page = "set"; pinErr = "";
            } else {
                pin = ""; pinErr = "Code incorrect";
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: theme.bg

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // --- Top status bar ------------------------------------------
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 56
                color: theme.pn
                Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 1; color: theme.ln }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20
                    spacing: 18

                    Rectangle {
                        width: 12; height: 12; radius: 6
                        color: window.hasAlarm ? theme.red : theme.green
                    }
                    Text {
                        text: frigo.unitName
                        color: theme.tx
                        font.family: theme.sans
                        font.pixelSize: 15
                        font.weight: Font.DemiBold
                        font.letterSpacing: 1.2
                    }
                    Rectangle { width: 1; height: 24; color: theme.ln }
                    Text {
                        text: {
                            const out = frigo.tempAverage < frigo.tempMinC || frigo.tempAverage > frigo.tempMaxC;
                            if (out) return "Régulation · hors plage";
                            return frigo.compressorOn ? "Régulation · compresseur ON" : "Régulation · veille";
                        }
                        color: theme.mt
                        font.family: theme.mono
                        font.pixelSize: 15
                    }
                    Item { Layout.fillWidth: true }
                    Text {
                        id: clockText
                        text: Qt.formatDateTime(new Date(), "hh:mm:ss")
                        color: theme.tx
                        font.family: theme.mono
                        font.pixelSize: 16
                        font.weight: Font.Medium
                        Timer { interval: 1000; running: true; repeat: true; onTriggered: clockText.text = Qt.formatDateTime(new Date(), "hh:mm:ss") }
                    }
                    Text {
                        text: Qt.formatDateTime(new Date(), "dd/MM/yyyy")
                        color: theme.mt
                        font.family: theme.mono
                        font.pixelSize: 14
                    }
                    Rectangle {
                        width: 64; height: 36; radius: 4
                        color: theme.bg
                        border.color: theme.ln
                        border.width: 1
                        Text {
                            anchors.centerIn: parent
                            text: theme.dark ? "JOUR" : "NUIT"
                            font.pixelSize: 13
                            font.weight: Font.DemiBold
                            font.family: theme.sans
                            color: theme.tx
                        }
                        MouseArea { anchors.fill: parent; onClicked: frigo.darkTheme = !frigo.darkTheme }
                    }
                }
            }

            // --- Alarm banner -----------------------------------------------
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: (window.hasAlarm && window.page !== "alarms") ? 44 : 0
                clip: true
                color: "#b91c1c"
                visible: height > 0
                Behavior on Layout.preferredHeight { NumberAnimation { duration: 120 } }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20
                    spacing: 14

                    Rectangle {
                        width: 10; height: 10; color: "white"
                        SequentialAnimation on opacity {
                            loops: Animation.Infinite
                            NumberAnimation { from: 1; to: 0.35; duration: 550 }
                            NumberAnimation { from: 0.35; to: 1; duration: 550 }
                        }
                    }
                    Text {
                        text: frigo.errorLog.topActiveSummary
                        color: "white"
                        font.family: theme.sans
                        font.pixelSize: 16
                        font.weight: Font.DemiBold
                    }
                    Item { Layout.fillWidth: true }
                    Text { text: "Voir les alarmes ›"; color: "white"; opacity: 0.85; font.family: theme.sans; font.pixelSize: 14 }
                }
                MouseArea { anchors.fill: parent; onClicked: window.page = "alarms" }
            }

            // --- Content ------------------------------------------------
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                TempPage { anchors.fill: parent; visible: window.page === "temp" }
                HistPage { anchors.fill: parent; visible: window.page === "hist" }
                AlarmsPage { anchors.fill: parent; visible: window.page === "alarms" }
                SettingsPage {
                    anchors.fill: parent
                    visible: window.page === "set"
                    onLocked: window.page = "temp"
                    onEnterMaintenance: window.page = "maint"
                }
                MaintenancePage {
                    anchors.fill: parent
                    visible: window.page === "maint"
                    onExited: window.page = "set"
                }
            }

            // --- Bottom nav -----------------------------------------------
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 84
                color: theme.pn
                Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; height: 1; color: theme.ln }

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Repeater {
                        model: [
                            { k: "temp", label: "Température", shape: 13 },
                            { k: "hist", label: "Historique", shape: 3 },
                            { k: "alarms", label: "Alarmes", shape: 3 },
                            { k: "set", label: "Réglages", shape: 13 }
                        ]
                        delegate: Rectangle {
                            required property var modelData
                            readonly property bool on: window.page === modelData.k
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            color: theme.selBgFor(on)
                            Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; height: 3; color: theme.selMark(on) }

                            ColumnLayout {
                                anchors.centerIn: parent
                                spacing: 8
                                Rectangle {
                                    Layout.alignment: Qt.AlignHCenter
                                    width: 26; height: 26
                                    radius: modelData.shape
                                    color: "transparent"
                                    border.width: 2.5
                                    border.color: theme.selColor(on)
                                }
                                Text {
                                    Layout.alignment: Qt.AlignHCenter
                                    text: modelData.label
                                    font.family: theme.sans
                                    font.pixelSize: 16
                                    font.weight: Font.DemiBold
                                    font.letterSpacing: 0.6
                                    color: theme.selColor(on)
                                }
                            }

                            Rectangle {
                                visible: modelData.k === "alarms" && window.activeAlarms > 0
                                anchors.top: parent.top
                                anchors.topMargin: 12
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.horizontalCenterOffset: 24
                                width: Math.max(24, badgeText.implicitWidth + 12)
                                height: 24
                                radius: 12
                                color: theme.red
                                Text {
                                    id: badgeText
                                    anchors.centerIn: parent
                                    text: String(window.activeAlarms)
                                    color: "white"
                                    font.pixelSize: 14
                                    font.weight: Font.Bold
                                    font.family: theme.sans
                                }
                            }

                            MouseArea { anchors.fill: parent; onClicked: window.go(modelData.k) }
                        }
                    }
                }
            }
        }

        // --- Alarm edge overlay --------------------------------------------
        Rectangle {
            anchors.fill: parent
            visible: window.hasAlarm
            color: "transparent"
            border.width: 8
            border.color: "#ef4444"
            z: 40

            SequentialAnimation on border.color {
                running: window.hasAlarm
                loops: Animation.Infinite
                ColorAnimation { from: "#ef4444"; to: "#7f1d1d"; duration: 550 }
                ColorAnimation { from: "#7f1d1d"; to: "#ef4444"; duration: 550 }
            }
        }

        // --- PIN modal ----------------------------------------------------
        Rectangle {
            anchors.fill: parent
            visible: window.showPin
            color: Qt.rgba(6 / 255, 9 / 255, 12 / 255, 0.88)
            z: 50

            MouseArea { anchors.fill: parent }

            Rectangle {
                width: 420
                height: pinCol.implicitHeight + 48
                anchors.centerIn: parent
                radius: 8
                color: theme.pn
                border.color: theme.ln
                border.width: 1

                ColumnLayout {
                    id: pinCol
                    anchors.fill: parent
                    anchors.margins: 24
                    spacing: 16

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "Accès réglages"; color: theme.tx; font.family: theme.sans; font.pixelSize: 20; font.weight: Font.Bold }
                        Item { Layout.fillWidth: true }
                        Text {
                            text: "Annuler"
                            color: theme.mt
                            font.family: theme.sans
                            font.pixelSize: 15
                            MouseArea { anchors.fill: parent; anchors.margins: -8; onClicked: { window.showPin = false; window.pin = ""; window.pinErr = ""; } }
                        }
                    }
                    Text {
                        text: window.pinErr || "Saisissez le code technicien"
                        color: window.pinErr ? theme.red : theme.mt
                        font.family: theme.sans
                        font.pixelSize: 14
                    }
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 64
                        radius: 5
                        color: theme.bg
                        border.color: theme.ln
                        border.width: 1
                        Text {
                            anchors.centerIn: parent
                            text: "••••".slice(0, window.pin.length) + "____".slice(0, 4 - window.pin.length)
                            font.family: theme.mono
                            font.pixelSize: 38
                            font.letterSpacing: 14
                            color: theme.tx
                        }
                    }
                    NumPad {
                        Layout.fillWidth: true
                        keyHeight: 64
                        keyBg: theme.bg
                        fontSize: 26
                        onKeyPressed: (k) => window.pinPress(k)
                    }
                }
            }
        }
    }
}
