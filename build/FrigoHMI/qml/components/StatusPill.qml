import QtQuick

// Small colored badge: "label: state" (e.g. "Porte: Ouverte").
Rectangle {
    id: root
    property string label: ""
    property bool active: false
    property color activeColor: "#ff5a5a"
    property color inactiveColor: "#2c4863"
    property string activeText: "Actif"
    property string inactiveText: "OK"

    implicitWidth: row.width + 24
    implicitHeight: 40
    radius: 20
    color: active ? Qt.darker(activeColor, 1.6) : "#152a40"
    border.color: active ? activeColor : "#2c4863"
    border.width: 1

    Row {
        id: row
        anchors.centerIn: parent
        spacing: 8
        Rectangle {
            width: 10; height: 10; radius: 5
            anchors.verticalCenter: parent.verticalCenter
            color: root.active ? root.activeColor : "#4c6d8c"
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.label + ": " + (root.active ? root.activeText : root.inactiveText)
            color: "#e8f0fa"
            font.pixelSize: 14
        }
    }
}
