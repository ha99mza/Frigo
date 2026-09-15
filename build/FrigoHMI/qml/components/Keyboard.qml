import QtQuick
import QtQuick.Layouts
import QtQuick.Window

// On-screen QWERTY keyboard for free-text entry (Wi-Fi passwords). Not a
// modal by itself — the caller wraps it in whatever overlay/dialog chrome
// it needs and reacts to accepted()/cancelled().
Item {
    id: root
    readonly property QtObject theme: Window.window.theme

    property string title: "Saisir le texte"
    property string value: ""
    property bool isPassword: true
    property bool maskVisible: false
    property bool shift: false
    property bool symbols: false

    signal accepted(string value)
    signal cancelled

    readonly property var rowLetters1: ["q", "w", "e", "r", "t", "y", "u", "i", "o", "p"]
    readonly property var rowLetters2: ["a", "s", "d", "f", "g", "h", "j", "k", "l"]
    readonly property var rowLetters3: ["z", "x", "c", "v", "b", "n", "m"]
    readonly property var rowSymbols1: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
    readonly property var rowSymbols2: ["-", "_", "@", "#", "$", "%", "&", "*", "(", ")"]
    readonly property var rowSymbols3: ["!", "?", ".", ",", ":", ";", "+", "="]

    function keyTap(k) { root.value += (root.shift && !root.symbols) ? k.toUpperCase() : k }
    function backspace() { root.value = root.value.slice(0, -1) }
    function displayKey(k) { return (root.shift && !root.symbols) ? k.toUpperCase() : k }

    // Inline components compile as separate types and can't see this file's
    // outer `theme` property, so it resolves its own (same Window.window
    // pattern every other file uses — safe regardless of compilation unit).
    component Key: Rectangle {
        id: key
        readonly property QtObject theme: Window.window.theme
        property string label: ""
        property bool wide: false
        property bool active: false
        signal tapped
        Layout.fillWidth: !wide
        Layout.preferredWidth: wide ? 84 : -1
        Layout.preferredHeight: 52
        radius: 5
        color: active ? theme.accent : theme.pn
        border.color: theme.ln
        border.width: 1
        Text {
            anchors.centerIn: parent
            text: key.label
            font.family: theme.mono
            font.pixelSize: 17
            font.weight: Font.DemiBold
            color: key.active ? "#08222f" : theme.tx
        }
        MouseArea { anchors.fill: parent; onClicked: key.tapped() }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            Text { text: root.title; color: theme.tx; font.family: theme.sans; font.pixelSize: 20; font.weight: Font.Bold }
            Item { Layout.fillWidth: true }
            Text {
                text: "Annuler"
                color: theme.mt
                font.family: theme.sans
                font.pixelSize: 15
                MouseArea { anchors.fill: parent; anchors.margins: -10; onClicked: root.cancelled() }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 56
                radius: 5
                color: theme.bg
                border.color: theme.ln
                border.width: 1
                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 14
                    anchors.rightMargin: 14
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideLeft
                    text: (root.isPassword && !root.maskVisible) ? "•".repeat(root.value.length) : root.value
                    color: theme.tx
                    font.family: theme.mono
                    font.pixelSize: 20
                }
            }
            Rectangle {
                visible: root.isPassword
                Layout.preferredWidth: 96
                Layout.preferredHeight: 56
                radius: 5
                color: theme.pn
                border.color: theme.ln
                border.width: 1
                Text {
                    anchors.centerIn: parent
                    text: root.maskVisible ? "MASQUER" : "AFFICHER"
                    font.family: theme.sans
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                    color: theme.mt
                }
                MouseArea { anchors.fill: parent; onClicked: root.maskVisible = !root.maskVisible }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 6
            Repeater {
                model: root.symbols ? root.rowSymbols1 : root.rowLetters1
                delegate: Key {
                    required property string modelData
                    label: root.displayKey(modelData)
                    onTapped: root.keyTap(modelData)
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 6
            Item { Layout.preferredWidth: 26 }
            Repeater {
                model: root.symbols ? root.rowSymbols2 : root.rowLetters2
                delegate: Key {
                    required property string modelData
                    label: root.displayKey(modelData)
                    onTapped: root.keyTap(modelData)
                }
            }
            Item { Layout.preferredWidth: 26 }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 6
            Key {
                visible: !root.symbols
                label: "⇧"
                wide: true
                active: root.shift
                onTapped: root.shift = !root.shift
            }
            Repeater {
                model: root.symbols ? root.rowSymbols3 : root.rowLetters3
                delegate: Key {
                    required property string modelData
                    label: root.displayKey(modelData)
                    onTapped: root.keyTap(modelData)
                }
            }
            Key { label: "⌫"; wide: true; onTapped: root.backspace() }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 6
            Key {
                label: root.symbols ? "ABC" : "123"
                wide: true
                onTapped: { root.symbols = !root.symbols; root.shift = false }
            }
            Key { label: ""; onTapped: root.value += " " }
            Rectangle {
                Layout.preferredWidth: 120
                Layout.preferredHeight: 52
                radius: 5
                color: theme.accent
                Text { anchors.centerIn: parent; text: "OK"; font.family: theme.sans; font.pixelSize: 18; font.weight: Font.Bold; color: "#08222f" }
                MouseArea { anchors.fill: parent; onClicked: root.accepted(root.value) }
            }
        }
    }
}
