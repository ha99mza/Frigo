import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window
import "components"

Item {
    id: root
    readonly property QtObject theme: Window.window.theme
    property string mtab: "cal"
    signal exited

    property string pwNew: ""
    property string pwConf: ""
    property string pwField: "new"
    property string pwMsg: ""
    property color pwMsgColor: theme.mt

    function pwPress(k) {
        const targetIsNew = pwField === "new";
        if (k === "del") {
            if (targetIsNew) root.pwNew = root.pwNew.slice(0, -1);
            else root.pwConf = root.pwConf.slice(0, -1);
            root.pwMsg = "";
            return;
        }
        if (k === "ok") {
            if (root.pwNew.length !== 4) {
                root.pwMsg = "Le code doit contenir 4 chiffres";
                root.pwMsgColor = theme.red;
                root.pwField = "new";
                return;
            }
            if (root.pwNew !== root.pwConf) {
                root.pwMsg = "Les deux codes ne correspondent pas";
                root.pwMsgColor = theme.red;
                root.pwConf = "";
                root.pwField = "conf";
                return;
            }
            if (frigo.changeSettingsPin(root.pwNew)) {
                root.pwMsg = "Code enregistré";
                root.pwMsgColor = theme.green;
            } else {
                root.pwMsg = "Échec de l'enregistrement";
                root.pwMsgColor = theme.red;
            }
            root.pwNew = ""; root.pwConf = ""; root.pwField = "new";
            return;
        }
        if (targetIsNew) {
            if (root.pwNew.length < 4) root.pwNew += k;
            if (root.pwNew.length === 4) root.pwField = "conf";
        } else {
            if (root.pwConf.length < 4) root.pwConf += k;
        }
        root.pwMsg = "";
    }

    function mask(s) { return "••••".slice(0, s.length) + "____".slice(0, 4 - s.length); }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.preferredWidth: 208
            Layout.fillHeight: true
            color: theme.pn

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                anchors.topMargin: 14
                spacing: 8

                Text {
                    text: "MAINTENANCE"
                    color: theme.amber
                    font.family: theme.sans
                    font.pixelSize: 12
                    font.weight: Font.Bold
                    font.letterSpacing: 1.4
                    Layout.leftMargin: 4
                    Layout.bottomMargin: 4
                }

                Repeater {
                    model: [
                        { k: "cal", label: "1 · Capteurs" },
                        { k: "fan", label: "2 · Ventilateurs" },
                        { k: "act", label: "3 · Actionneurs" },
                        { k: "pwd", label: "4 · Code d'accès" }
                    ]
                    delegate: Rectangle {
                        required property var modelData
                        readonly property bool on: root.mtab === modelData.k
                        Layout.fillWidth: true
                        Layout.preferredHeight: 60
                        radius: 5
                        color: theme.selBgFor(on)
                        Rectangle { width: 3; height: parent.height; color: theme.selMark(on) }
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 14
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.label
                            font.family: theme.sans
                            font.pixelSize: 15
                            font.weight: Font.DemiBold
                            color: theme.selColor(on)
                        }
                        MouseArea { anchors.fill: parent; onClicked: root.mtab = modelData.k }
                    }
                }

                Item { Layout.fillHeight: true }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 60
                    radius: 5
                    color: theme.amber
                    Text { anchors.centerIn: parent; text: "Quitter"; color: "#1a1204"; font.family: theme.sans; font.pixelSize: 15; font.weight: Font.Bold }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            frigo.commandMaintenanceMode(false);
                            root.exited();
                        }
                    }
                }
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            contentWidth: availableWidth

            ColumnLayout {
                width: parent.width
                spacing: 12

                // --- 1. Capteurs ---------------------------------------
                GridLayout {
                    visible: root.mtab === "cal"
                    Layout.fillWidth: true
                    Layout.margins: 20
                    columns: 2
                    rowSpacing: 12
                    columnSpacing: 12

                    Repeater {
                        model: [
                            { label: "Capteur 1", raw: frigo.temp1, get: function() { return frigo.offsetCap1C }, set: function(v) { frigo.offsetCap1C = v } },
                            { label: "Capteur 2", raw: frigo.temp2, get: function() { return frigo.offsetCap2C }, set: function(v) { frigo.offsetCap2C = v } },
                            { label: "Capteur 3", raw: frigo.temp3, get: function() { return frigo.offsetCap3C }, set: function(v) { frigo.offsetCap3C = v } },
                            { label: "Capteur évaporateur", raw: frigo.tempEva, get: function() { return frigo.offsetEvaC }, set: function(v) { frigo.offsetEvaC = v } }
                        ]
                        delegate: Rectangle {
                            required property var modelData
                            Layout.fillWidth: true
                            Layout.preferredHeight: 150
                            radius: 6
                            color: theme.pn
                            border.color: theme.ln
                            border.width: 1

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 15
                                spacing: 8

                                RowLayout {
                                    Layout.fillWidth: true
                                    Text { text: modelData.label; color: theme.tx; font.family: theme.sans; font.pixelSize: 17; font.weight: Font.DemiBold }
                                    Item { Layout.fillWidth: true }
                                    Text { text: modelData.raw.toFixed(1) + " °C"; color: theme.mt; font.family: theme.mono; font.pixelSize: 15 }
                                }
                                Text { text: "OFFSET DE CALIBRATION (°C)"; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.2 }
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 10
                                    Rectangle {
                                        Layout.preferredWidth: 64; Layout.preferredHeight: 60
                                        radius: 5; color: theme.bg; border.color: theme.ln; border.width: 1
                                        Text { anchors.centerIn: parent; text: "−"; font.pixelSize: 30; font.weight: Font.DemiBold; color: theme.tx }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: modelData.set(Math.max(-5, Math.round((modelData.get() - 0.1) * 10) / 10))
                                        }
                                    }
                                    Rectangle {
                                        Layout.fillWidth: true; Layout.preferredHeight: 60
                                        radius: 5; color: theme.bg; border.color: theme.ln; border.width: 1
                                        Text {
                                            anchors.centerIn: parent
                                            text: (modelData.get() >= 0 ? "+" : "") + modelData.get().toFixed(1)
                                            font.family: theme.mono; font.pixelSize: 26; font.weight: Font.DemiBold; color: theme.accent
                                        }
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 64; Layout.preferredHeight: 60
                                        radius: 5; color: theme.bg; border.color: theme.ln; border.width: 1
                                        Text { anchors.centerIn: parent; text: "+"; font.pixelSize: 26; font.weight: Font.DemiBold; color: theme.tx }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: modelData.set(Math.min(5, Math.round((modelData.get() + 0.1) * 10) / 10))
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // --- 2. Ventilateurs -------------------------------------
                ColumnLayout {
                    visible: root.mtab === "fan"
                    Layout.fillWidth: true
                    Layout.margins: 20
                    spacing: 12

                    Text {
                        text: "5 ventilateurs · masque : " + (frigo.fan1On?"1":"0") + (frigo.fan2On?"1":"0") + (frigo.fan3On?"1":"0") + (frigo.fan4On?"1":"0") + (frigo.fan5On?"1":"0")
                        color: theme.mt; font.family: theme.mono; font.pixelSize: 13
                    }
                    GridLayout {
                        Layout.fillWidth: true
                        columns: 3
                        rowSpacing: 12
                        columnSpacing: 12
                        Repeater {
                            model: [
                                { label: "Ventilateur 1", on: frigo.fan1On, idx: 0 },
                                { label: "Ventilateur 2", on: frigo.fan2On, idx: 1 },
                                { label: "Ventilateur 3", on: frigo.fan3On, idx: 2 },
                                { label: "Ventilateur 4", on: frigo.fan4On, idx: 3 },
                                { label: "Ventilateur 5", on: frigo.fan5On, idx: 4 }
                            ]
                            delegate: Rectangle {
                                required property var modelData
                                Layout.fillWidth: true
                                Layout.preferredHeight: 104
                                radius: 6
                                color: theme.selBgFor(modelData.on)
                                border.color: modelData.on ? theme.accent : theme.ln
                                border.width: 1
                                ColumnLayout {
                                    anchors.fill: parent
                                    anchors.margins: 15
                                    spacing: 8
                                    Text { text: modelData.label; color: theme.tx; font.family: theme.sans; font.pixelSize: 17; font.weight: Font.DemiBold }
                                    RowLayout {
                                        spacing: 10
                                        Rectangle { width: 12; height: 12; radius: 6; color: modelData.on ? theme.accent : theme.ln }
                                        Text {
                                            text: modelData.on ? "Marche" : "Éteint"
                                            font.family: theme.sans; font.pixelSize: 15; font.weight: Font.DemiBold
                                            color: theme.selColor(modelData.on)
                                        }
                                    }
                                }
                                MouseArea { anchors.fill: parent; onClicked: frigo.toggleFanOverride(modelData.idx) }
                            }
                        }
                    }
                }

                // --- 3. Actionneurs --------------------------------------
                ColumnLayout {
                    visible: root.mtab === "act"
                    Layout.fillWidth: true
                    Layout.margins: 20
                    spacing: 12

                    Text {
                        text: "Commande manuelle des sorties — régulation suspendue"
                        color: theme.mt; font.family: theme.sans; font.pixelSize: 13
                    }
                    GridLayout {
                        Layout.fillWidth: true
                        columns: 2
                        rowSpacing: 12
                        columnSpacing: 12
                        Repeater {
                            model: [
                                { label: "Compresseur", on: frigo.compressorOn, key: "comp" },
                                { label: "Relais porte", on: frigo.doorRelayOn, key: "door" },
                                { label: "Lampe", on: frigo.lampOn, key: "lamp" },
                                { label: "Ventilateur dégivrage", on: frigo.defrostFanOn, key: "dfan" }
                            ]
                            delegate: Rectangle {
                                required property var modelData
                                Layout.fillWidth: true
                                Layout.preferredHeight: 118
                                radius: 6
                                color: theme.selBgFor(modelData.on)
                                border.color: modelData.on ? theme.accent : theme.ln
                                border.width: 1
                                ColumnLayout {
                                    anchors.fill: parent
                                    anchors.margins: 17
                                    spacing: 10
                                    Text { text: modelData.label; color: theme.tx; font.family: theme.sans; font.pixelSize: 19; font.weight: Font.DemiBold }
                                    RowLayout {
                                        spacing: 10
                                        Rectangle { width: 14; height: 14; radius: 7; color: modelData.on ? theme.accent : theme.ln }
                                        Text {
                                            text: modelData.on ? "Marche" : "Éteint"
                                            font.family: theme.sans; font.pixelSize: 16; font.weight: Font.DemiBold
                                            color: theme.selColor(modelData.on)
                                        }
                                    }
                                }
                                MouseArea { anchors.fill: parent; onClicked: frigo.toggleRelayOverride(modelData.key) }
                            }
                        }
                    }
                }

                // --- 4. Code d'accès --------------------------------------
                RowLayout {
                    visible: root.mtab === "pwd"
                    Layout.fillWidth: true
                    Layout.margins: 20
                    spacing: 20

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 14

                        Text {
                            text: root.pwMsg || "Saisissez un nouveau code à 4 chiffres"
                            color: root.pwMsg ? root.pwMsgColor : theme.mt
                            font.family: theme.sans
                            font.pixelSize: 14
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }
                        ColumnLayout {
                            spacing: 6
                            Text { text: "NOUVEAU CODE"; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.3 }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 64
                                radius: 5
                                color: theme.pn
                                border.width: 2
                                border.color: root.pwField === "new" ? theme.accent : theme.ln
                                Text {
                                    anchors.centerIn: parent
                                    text: root.mask(root.pwNew)
                                    font.family: theme.mono; font.pixelSize: 30; font.letterSpacing: 10
                                    color: theme.tx
                                }
                                MouseArea { anchors.fill: parent; onClicked: root.pwField = "new" }
                            }
                        }
                        ColumnLayout {
                            spacing: 6
                            Text { text: "CONFIRMER"; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.3 }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 64
                                radius: 5
                                color: theme.pn
                                border.width: 2
                                border.color: root.pwField === "conf" ? theme.accent : theme.ln
                                Text {
                                    anchors.centerIn: parent
                                    text: root.mask(root.pwConf)
                                    font.family: theme.mono; font.pixelSize: 30; font.letterSpacing: 10
                                    color: theme.tx
                                }
                                MouseArea { anchors.fill: parent; onClicked: root.pwField = "conf" }
                            }
                        }
                    }

                    NumPad {
                        Layout.preferredWidth: 300
                        Layout.alignment: Qt.AlignTop
                        keyHeight: 56
                        keyBg: theme.pn
                        fontSize: 24
                        onKeyPressed: (k) => root.pwPress(k)
                    }
                }

                Item { Layout.preferredHeight: 12 }
            }
        }
    }
}
