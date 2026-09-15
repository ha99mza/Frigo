import QtQuick
import QtQuick.Layouts
import QtQuick.Window

// One editable configuration row matching the design: label + hint on the
// left, a big mono value display, and −/+ buttons.
Rectangle {
    id: root
    readonly property QtObject theme: Window.window.theme
    property string label: ""
    property string hint: ""
    property real value: 0
    property real step: 1
    property real min: 0
    property real max: 100
    property int decimals: 0
    property string unit: ""
    signal decClicked
    signal incClicked

    Layout.fillWidth: true
    Layout.preferredHeight: 88
    radius: 6
    color: theme.pn
    border.color: theme.ln
    border.width: 1

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 16
        anchors.rightMargin: 16
        spacing: 18

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 3
            Text {
                text: root.label
                color: theme.tx
                font.family: theme.sans
                font.pixelSize: 18
                font.weight: Font.DemiBold
            }
            Text {
                text: root.hint
                color: theme.mt
                font.family: theme.sans
                font.pixelSize: 13
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        Text {
            Layout.preferredWidth: 150
            horizontalAlignment: Text.AlignRight
            text: root.value.toFixed(root.decimals) + " " + root.unit
            color: theme.accent
            font.family: theme.mono
            font.pixelSize: 30
            font.weight: Font.DemiBold
        }

        RowLayout {
            spacing: 8
            Rectangle {
                Layout.preferredWidth: 68
                Layout.preferredHeight: 64
                radius: 5
                color: theme.bg
                border.color: theme.ln
                border.width: 1
                enabled: root.value > root.min
                opacity: enabled ? 1 : 0.4
                Text {
                    anchors.centerIn: parent
                    text: "−"
                    font.pixelSize: 32
                    font.weight: Font.DemiBold
                    color: theme.tx
                }
                MouseArea { anchors.fill: parent; onClicked: root.decClicked() }
            }
            Rectangle {
                Layout.preferredWidth: 68
                Layout.preferredHeight: 64
                radius: 5
                color: theme.bg
                border.color: theme.ln
                border.width: 1
                enabled: root.value < root.max
                opacity: enabled ? 1 : 0.4
                Text {
                    anchors.centerIn: parent
                    text: "+"
                    font.pixelSize: 28
                    font.weight: Font.DemiBold
                    color: theme.tx
                }
                MouseArea { anchors.fill: parent; onClicked: root.incClicked() }
            }
        }
    }
}
