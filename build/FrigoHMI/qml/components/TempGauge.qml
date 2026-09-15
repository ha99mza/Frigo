import QtQuick

// Compact temperature readout: big value + label, color-coded by range.
Rectangle {
    id: root
    property string label: ""
    property real value: 0
    property real warnLow: -50
    property real warnHigh: 50
    property bool big: false

    color: "#132338"
    radius: 14
    border.color: "#22415f"
    border.width: 1

    readonly property color valueColor: {
        if (value <= warnLow || value >= warnHigh) return "#ff5a5a"
        if (value < 0) return "#5ab6ff"
        return "#5affa0"
    }

    Column {
        anchors.centerIn: parent
        spacing: 2
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.value.toFixed(1) + " °C"
            color: root.valueColor
            font.pixelSize: root.big ? 54 : 30
            font.bold: true
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.label
            color: "#8fa5c0"
            font.pixelSize: root.big ? 16 : 13
        }
    }
}
