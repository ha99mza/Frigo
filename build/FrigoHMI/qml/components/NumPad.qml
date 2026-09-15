import QtQuick
import QtQuick.Layouts
import QtQuick.Window

// Reusable numeric keypad: 1-9, ← (delete), 0, OK. Used by the PIN unlock
// modal and the maintenance "Code d'accès" screen.
GridLayout {
    id: root
    readonly property QtObject theme: Window.window.theme
    columns: 3
    rowSpacing: 8
    columnSpacing: 8

    property real keyHeight: 64
    property color keyBg: theme.bg
    property real fontSize: 26
    signal keyPressed(string key)

    Repeater {
        model: ["1","2","3","4","5","6","7","8","9","del","0","ok"]
        delegate: Rectangle {
            required property string modelData
            Layout.preferredHeight: root.keyHeight
            Layout.fillWidth: true
            radius: 5
            color: root.keyBg
            border.color: theme.ln
            border.width: 1

            readonly property bool isSpecial: modelData === "del" || modelData === "ok"

            Text {
                anchors.centerIn: parent
                text: modelData === "del" ? "←" : (modelData === "ok" ? "OK" : modelData)
                font.family: theme.mono
                font.pixelSize: root.fontSize
                font.weight: Font.DemiBold
                color: isSpecial ? theme.accent : theme.tx
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.keyPressed(modelData)
            }
        }
    }
}
