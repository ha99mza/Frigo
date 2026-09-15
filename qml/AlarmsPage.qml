import QtQuick
import QtQuick.Layouts
import QtQuick.Window

Item {
    id: root
    readonly property QtObject theme: Window.window.theme

    function severityColor(code) {
        if (code === 0x52 || code === 0x53) return theme.amber; // door / defrost timeout
        return theme.red; // temp limit, sensors, RTC/flash/EEPROM faults
    }

    function detailFor(code) {
        switch (code) {
        case 0x52: return "Délai de " + frigo.doorAlarmDelaySeconds.toFixed(0) + " s dépassé";
        case 0x51: return "Hors plage " + frigo.tempMinC.toFixed(1) + " … " + frigo.tempMaxC.toFixed(1) + " °C pendant plus de " + frigo.tempLimitTimeoutMinutes.toFixed(0) + " min";
        case 0x53: return "Arrêt forcé après " + frigo.defrostTimeoutMinutes.toFixed(0) + " min";
        case 0x21: case 0x22: case 0x23: case 0x24:
            return "Vérifier le câblage du capteur";
        case 0x11: case 0x12: case 0x13:
            return "Défaut horloge temps réel (RTC)";
        case 0x31: case 0x32: case 0x33:
            return "Défaut mémoire Flash";
        case 0x41: case 0x42: case 0x43:
            return "Défaut mémoire EEPROM";
        default: return "";
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: 14

        RowLayout {
            Layout.fillWidth: true
            spacing: 14
            Text {
                text: "JOURNAL DES ALARMES"
                color: theme.mt
                font.family: theme.sans
                font.pixelSize: 14
                font.weight: Font.DemiBold
                font.letterSpacing: 2
            }
            Item { Layout.fillWidth: true }
            Rectangle {
                width: 168; height: 52; radius: 5
                color: "#b91c1c"
                Text { anchors.centerIn: parent; text: "Acquitter tout"; color: "white"; font.pixelSize: 16; font.weight: Font.DemiBold; font.family: theme.sans }
                MouseArea { anchors.fill: parent; onClicked: frigo.acknowledgeAllAlarms() }
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 10
            model: frigo.errorLog

            delegate: Rectangle {
                width: ListView.view.width
                height: 76
                radius: 6
                color: theme.pn
                border.color: theme.ln
                border.width: 1

                Rectangle {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 4
                    color: root.severityColor(model.code)
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 18
                    anchors.rightMargin: 18
                    spacing: 16

                    Text {
                        Layout.preferredWidth: 96
                        text: Qt.formatDateTime(model.timestamp, "hh:mm:ss")
                        color: theme.mt
                        font.family: theme.mono
                        font.pixelSize: 15
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 3
                        Text { text: model.description; color: theme.tx; font.family: theme.sans; font.pixelSize: 19; font.weight: Font.DemiBold }
                        Text {
                            text: root.detailFor(model.code)
                            color: theme.mt; font.family: theme.sans; font.pixelSize: 14
                            visible: text.length > 0
                        }
                    }
                    Rectangle {
                        Layout.preferredWidth: stateLabel.implicitWidth + 28
                        Layout.preferredHeight: 32
                        radius: 3
                        color: "transparent"
                        border.color: root.severityColor(model.code)
                        border.width: 1
                        Text {
                            id: stateLabel
                            anchors.centerIn: parent
                            text: model.active ? "ACTIVE" : "RÉSOLUE"
                            color: root.severityColor(model.code)
                            font.pixelSize: 13
                            font.weight: Font.DemiBold
                            font.letterSpacing: 1
                            font.family: theme.sans
                        }
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                visible: parent.count === 0
                text: "Aucune alarme enregistrée"
                color: theme.mt
                font.family: theme.sans
                font.pixelSize: 16
            }
        }
    }
}
