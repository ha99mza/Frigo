import QtQuick

// Icon + label tile showing a single relay's on/off state.
Rectangle {
    id: root
    property string label: ""
    property string iconGlyph: "●"
    property bool on: false

    implicitWidth: 92
    implicitHeight: 88
    radius: 12
    color: on ? "#1d3f2a" : "#152436"
    border.color: on ? "#3ecf7d" : "#22354a"
    border.width: 1.5

    Column {
        anchors.centerIn: parent
        spacing: 6
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.iconGlyph
            font.pixelSize: 26
            color: root.on ? "#3ecf7d" : "#4c6d8c"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.label
            font.pixelSize: 12
            color: root.on ? "#c9f5da" : "#7f96ac"
        }
    }
}
