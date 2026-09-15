import QtQuick
import QtQuick.Controls

// Full-width red banner shown while at least one error is active.
Rectangle {
    id: root
    visible: frigo.errorLog.activeCount > 0
    height: visible ? 48 : 0
    color: "#8a1f1f"

    Behavior on height { NumberAnimation { duration: 150 } }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 16
        spacing: 12

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "⚠"
            color: "#ffd0d0"
            font.pixelSize: 22
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: frigo.errorLog.activeCount + " alarme(s) active(s) — voir l'onglet Erreurs"
            color: "#ffffff"
            font.pixelSize: 16
            font.bold: true
        }
    }

    Button {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 12
        text: "Acquitter"
        onClicked: frigo.acknowledgeDoorAlarm()
    }
}
