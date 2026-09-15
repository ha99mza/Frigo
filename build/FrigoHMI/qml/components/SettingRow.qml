import QtQuick
import QtQuick.Controls

// One editable configuration row: label, unit, and a decimal-capable spin
// box. `value`/`valueModified` are the two-way binding surface — the parent
// screen owns the actual FrigoController property.
Rectangle {
    id: root
    property string label: ""
    property string unit: ""
    property real value: 0
    property real from: 0
    property real to: 100
    property real stepSize: 1
    property int decimals: 0
    signal valueModified(real newValue)

    readonly property int factor: Math.pow(10, decimals)

    implicitHeight: 64
    color: "transparent"
    border.color: "#22354a"
    border.width: 1
    radius: 8

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 12

        Text {
            width: 340
            anchors.verticalCenter: parent.verticalCenter
            text: root.label
            color: "#e8f0fa"
            font.pixelSize: 16
            elide: Text.ElideRight
        }

        SpinBox {
            id: spin
            anchors.verticalCenter: parent.verticalCenter
            from: Math.round(root.from * root.factor)
            to: Math.round(root.to * root.factor)
            stepSize: Math.max(1, Math.round(root.stepSize * root.factor))
            value: Math.round(root.value * root.factor)
            editable: true
            implicitWidth: 190
            implicitHeight: 44

            textFromValue: function(v) { return (v / root.factor).toFixed(root.decimals) }
            valueFromText: function(t) { return Math.round(parseFloat(t) * root.factor) }

            onValueModified: root.valueModified(spin.value / root.factor)
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.unit
            color: "#8fa5c0"
            font.pixelSize: 14
        }
    }
}
