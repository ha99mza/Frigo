import QtQuick
import QtQuick.Controls

// Touch-friendly side navigation button used in Main.qml's rail.
Button {
    id: root
    property string iconGlyph: "•"
    checkable: true
    implicitWidth: 108
    implicitHeight: 84

    background: Rectangle {
        color: root.checked ? "#1f3a5f" : "transparent"
        border.color: root.checked ? "#3f7fd6" : "transparent"
        border.width: 2
        radius: 10
    }

    contentItem: Column {
        spacing: 4
        anchors.centerIn: parent
        Text {
            text: root.iconGlyph
            font.pixelSize: 26
            color: root.checked ? "#ffffff" : "#8fa5c0"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: root.text
            font.pixelSize: 12
            color: root.checked ? "#ffffff" : "#8fa5c0"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
