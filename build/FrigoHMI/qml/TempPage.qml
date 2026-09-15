import QtQuick
import QtQuick.Layouts
import QtQuick.Window

Item {
    id: root
    readonly property QtObject theme: Window.window.theme

    readonly property bool outOfRange: frigo.tempAverage < frigo.tempMinC || frigo.tempAverage > frigo.tempMaxC
    readonly property color tempColor: outOfRange ? theme.red : theme.tx

    function formatLastDefrost() {
        const ts = frigo.lastDefrostEvent();
        if (!ts) return "—";
        return Qt.formatDateTime(new Date(ts * 1000), "hh:mm");
    }

    Timer {
        interval: 30000; running: true; repeat: true
        onTriggered: lastDefrostLabel.text = root.formatLastDefrost()
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 16
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        radius: 6
        color: theme.pn
        border.color: theme.ln
        border.width: 1
        clip: true

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 24
            anchors.topMargin: 18
            anchors.bottomMargin: 14
            spacing: 14

            RowLayout {
                Layout.fillWidth: true
                spacing: 14
                Text {
                    text: "TEMPÉRATURE CHAMBRE"
                    color: theme.mt
                    font.family: theme.sans
                    font.pixelSize: 14
                    font.weight: Font.DemiBold
                    font.letterSpacing: 2
                }
                Text {
                    text: "moyenne 3 sondes · mise à jour 2 s"
                    color: theme.mt
                    font.family: theme.mono
                    font.pixelSize: 13
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 10

                Text {
                    Layout.alignment: Qt.AlignVCenter
                    text: frigo.tempAverage.toFixed(1)
                    color: root.tempColor
                    font.family: theme.mono
                    font.pixelSize: 150
                    font.weight: Font.DemiBold
                    font.letterSpacing: -4
                }
                Text {
                    Layout.alignment: Qt.AlignBottom
                    Layout.bottomMargin: 22
                    text: "°C"
                    color: theme.mt
                    font.family: theme.mono
                    font.pixelSize: 52
                    font.weight: Font.Normal
                }
                Item { Layout.fillWidth: true }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: theme.ln
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 56
                spacing: 10

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 6
                    Text { text: "PLAGE AUTORISÉE"; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.2 }
                    Text {
                        text: frigo.tempMinC.toFixed(1) + " … " + frigo.tempMaxC.toFixed(1) + " °C"
                        color: theme.tx; font.family: theme.mono; font.pixelSize: 22; font.weight: Font.Medium
                    }
                }
                Rectangle { Layout.preferredWidth: 1; Layout.fillHeight: true; color: theme.ln }
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 6
                    Text { text: "ÉVAPORATEUR"; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.2 }
                    Text {
                        text: frigo.tempEva.toFixed(1) + " °C"
                        color: theme.tx; font.family: theme.mono; font.pixelSize: 22; font.weight: Font.Medium
                    }
                }
                Rectangle { Layout.preferredWidth: 1; Layout.fillHeight: true; color: theme.ln }
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 6
                    Text { text: "DERNIER DÉGIVRAGE"; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.2 }
                    Text {
                        id: lastDefrostLabel
                        text: root.formatLastDefrost()
                        color: theme.tx; font.family: theme.mono; font.pixelSize: 22; font.weight: Font.Medium
                    }
                }
            }
        }
    }
}
