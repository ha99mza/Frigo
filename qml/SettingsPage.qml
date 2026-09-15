import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Window
import "components"

Item {
    id: root
    readonly property QtObject theme: Window.window.theme
    property string setTab: "reg"
    signal locked
    signal enterMaintenance

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // --- Left tab rail ---------------------------------------------
        Rectangle {
            Layout.preferredWidth: 208
            Layout.fillHeight: true
            color: theme.pn

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                anchors.topMargin: 16
                spacing: 8

                Repeater {
                    model: [
                        { k: "reg", label: "Régulation" },
                        { k: "deg", label: "Dégivrage" },
                        { k: "alm", label: "Alarmes" },
                        { k: "net", label: "Réseau" },
                        { k: "mnt", label: "Maintenance" }
                    ]
                    delegate: Rectangle {
                        required property var modelData
                        readonly property bool on: root.setTab === modelData.k
                        Layout.fillWidth: true
                        Layout.preferredHeight: 64
                        radius: 5
                        color: theme.selBgFor(on)
                        Rectangle { width: 3; height: parent.height; color: theme.selMark(on) }
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 16
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.label
                            font.family: theme.sans
                            font.pixelSize: 16
                            font.weight: Font.DemiBold
                            color: theme.selColor(on)
                        }
                        MouseArea { anchors.fill: parent; onClicked: root.setTab = modelData.k }
                    }
                }

                Item { Layout.fillHeight: true }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 56
                    radius: 5
                    color: "transparent"
                    border.color: theme.ln
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        text: "Verrouiller"
                        color: theme.mt
                        font.family: theme.sans
                        font.pixelSize: 14
                        font.weight: Font.DemiBold
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: { frigo.lockSettings(); root.locked(); }
                    }
                }
            }
        }

        // --- Right content -----------------------------------------------
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            contentWidth: availableWidth

            ColumnLayout {
                width: parent.width
                spacing: 12
                anchors.margins: 20

                Item { Layout.preferredHeight: 4 }

                ColumnLayout {
                    visible: root.setTab === "reg"
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    spacing: 12
                    SettingsRow {
                        label: "Température min"; hint: "Seuil bas de régulation"; unit: "°C"
                        value: frigo.tempMinC; min: -20; max: 10; step: 0.5; decimals: 1
                        onDecClicked: frigo.tempMinC = Math.max(min, Math.round((value - step) * 10) / 10)
                        onIncClicked: frigo.tempMinC = Math.min(max, Math.round((value + step) * 10) / 10)
                    }
                    SettingsRow {
                        label: "Température max"; hint: "Seuil haut de régulation"; unit: "°C"
                        value: frigo.tempMaxC; min: -10; max: 20; step: 0.5; decimals: 1
                        onDecClicked: frigo.tempMaxC = Math.max(min, Math.round((value - step) * 10) / 10)
                        onIncClicked: frigo.tempMaxC = Math.min(max, Math.round((value + step) * 10) / 10)
                    }
                    SettingsRow {
                        label: "Température évaporateur min"; hint: "Protection givrage évaporateur"; unit: "°C"
                        value: frigo.tempEvaMinC; min: -35; max: 0; step: 0.5; decimals: 1
                        onDecClicked: frigo.tempEvaMinC = Math.max(min, Math.round((value - step) * 10) / 10)
                        onIncClicked: frigo.tempEvaMinC = Math.min(max, Math.round((value + step) * 10) / 10)
                    }
                    SettingsRow {
                        label: "Anti short cycle delay"; hint: "Délai minimal entre deux démarrages compresseur"; unit: "min"
                        value: frigo.antiShortCycleDelayMinutes; min: 0; max: 30; step: 1; decimals: 0
                        onDecClicked: frigo.antiShortCycleDelayMinutes = Math.max(min, value - step)
                        onIncClicked: frigo.antiShortCycleDelayMinutes = Math.min(max, value + step)
                    }
                }

                ColumnLayout {
                    visible: root.setTab === "deg"
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    spacing: 12
                    SettingsRow {
                        label: "Intervalle dégivrage"; hint: "Temps entre deux cycles de dégivrage"; unit: "h"
                        value: frigo.defrostIntervalHours; min: 1; max: 24; step: 1; decimals: 0
                        onDecClicked: frigo.defrostIntervalHours = Math.max(min, value - step)
                        onIncClicked: frigo.defrostIntervalHours = Math.min(max, value + step)
                    }
                    SettingsRow {
                        label: "Durée dégivrage"; hint: "Durée nominale du cycle"; unit: "min"
                        value: frigo.defrostDurationMinutes; min: 1; max: 60; step: 1; decimals: 0
                        onDecClicked: frigo.defrostDurationMinutes = Math.max(min, value - step)
                        onIncClicked: frigo.defrostDurationMinutes = Math.min(max, value + step)
                    }
                    SettingsRow {
                        label: "Timeout dégivrage"; hint: "Arrêt forcé si la consigne de fin n'est pas atteinte"; unit: "min"
                        value: frigo.defrostTimeoutMinutes; min: 5; max: 120; step: 5; decimals: 0
                        onDecClicked: frigo.defrostTimeoutMinutes = Math.max(min, value - step)
                        onIncClicked: frigo.defrostTimeoutMinutes = Math.min(max, value + step)
                    }
                }

                ColumnLayout {
                    visible: root.setTab === "alm"
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    spacing: 12
                    SettingsRow {
                        label: "Timeout limite température"; hint: "Délai avant alarme si hors plage"; unit: "min"
                        value: frigo.tempLimitTimeoutMinutes; min: 5; max: 120; step: 5; decimals: 0
                        onDecClicked: frigo.tempLimitTimeoutMinutes = Math.max(min, value - step)
                        onIncClicked: frigo.tempLimitTimeoutMinutes = Math.min(max, value + step)
                    }
                    SettingsRow {
                        label: "Alarme porte ouverte"; hint: "Délai avant déclenchement"; unit: "s"
                        value: frigo.doorAlarmDelaySeconds; min: 10; max: 600; step: 10; decimals: 0
                        onDecClicked: frigo.doorAlarmDelaySeconds = Math.max(min, value - step)
                        onIncClicked: frigo.doorAlarmDelaySeconds = Math.min(max, value + step)
                    }
                }

                // --- Réseau (nmcli / NetworkManager) -----------------------
                ColumnLayout {
                    visible: root.setTab === "net"
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    spacing: 12

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 88
                        radius: 6
                        color: theme.pn
                        border.color: theme.ln
                        border.width: 1
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 16
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 3
                                Text { text: "Wi-Fi"; color: theme.tx; font.family: theme.sans; font.pixelSize: 18; font.weight: Font.DemiBold }
                                Text {
                                    text: !netmgr.available ? "NetworkManager (nmcli) introuvable"
                                          : !netmgr.wifiEnabled ? "Interface désactivée"
                                          : netmgr.wifiConnected ? "Connecté à " + netmgr.ssid + " · signal " + netmgr.signalStrength + " %"
                                          : "Activée, non connecté"
                                    color: theme.mt; font.family: theme.sans; font.pixelSize: 13
                                }
                            }
                            Rectangle {
                                Layout.preferredWidth: 120
                                Layout.preferredHeight: 64
                                radius: 5
                                opacity: netmgr.available ? 1 : 0.4
                                color: netmgr.wifiEnabled ? theme.accent : theme.bg
                                Text {
                                    anchors.centerIn: parent
                                    text: netmgr.wifiEnabled ? "ACTIF" : "ARRÊT"
                                    font.family: theme.sans; font.pixelSize: 17; font.weight: Font.Bold
                                    color: netmgr.wifiEnabled ? "#08222f" : theme.mt
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    enabled: netmgr.available
                                    onClicked: netmgr.setWifiEnabled(!netmgr.wifiEnabled)
                                }
                            }
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 190
                        radius: 6
                        color: theme.pn
                        border.color: theme.ln
                        border.width: 1
                        GridLayout {
                            anchors.fill: parent
                            anchors.margins: 18
                            columns: 2
                            rowSpacing: 18
                            columnSpacing: 24
                            Repeater {
                                model: [
                                    { k: "Adresse IP", v: netmgr.wifiConnected ? netmgr.ipAddress : "—" },
                                    { k: "Réseau (SSID)", v: netmgr.wifiConnected ? netmgr.ssid : "—" },
                                    { k: "Masque", v: netmgr.wifiConnected ? netmgr.subnetMask : "—" },
                                    { k: "Passerelle", v: netmgr.wifiConnected ? netmgr.gateway : "—" },
                                    { k: "Adresse MAC", v: netmgr.macAddress || "—" },
                                    { k: "Mode", v: "DHCP" }
                                ]
                                delegate: ColumnLayout {
                                    required property var modelData
                                    spacing: 5
                                    Text { text: modelData.k; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.3 }
                                    Text { text: modelData.v; color: theme.tx; font.family: theme.mono; font.pixelSize: 22; font.weight: Font.DemiBold }
                                }
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 64
                            radius: 5
                            opacity: (netmgr.available && !netmgr.busy) ? 1 : 0.4
                            color: theme.pn
                            border.color: theme.ln
                            border.width: 1
                            Text {
                                anchors.centerIn: parent
                                text: "Rechercher les réseaux"
                                color: theme.tx; font.family: theme.sans; font.pixelSize: 16; font.weight: Font.DemiBold
                            }
                            MouseArea {
                                anchors.fill: parent
                                enabled: netmgr.available && !netmgr.busy
                                onClicked: netmgr.rescan()
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 64
                            radius: 5
                            opacity: (netmgr.available && netmgr.wifiConnected && !netmgr.busy) ? 1 : 0.4
                            color: "transparent"
                            border.color: theme.accent
                            border.width: 1
                            Text {
                                anchors.centerIn: parent
                                text: netmgr.busy ? "Renouvellement…" : "Renouveler l'adresse IP"
                                color: theme.accent; font.family: theme.sans; font.pixelSize: 16; font.weight: Font.DemiBold
                            }
                            MouseArea {
                                anchors.fill: parent
                                enabled: netmgr.available && netmgr.wifiConnected && !netmgr.busy
                                onClicked: netmgr.renewIp()
                            }
                        }
                    }
                }

                // --- Maintenance summary -----------------------------------
                ColumnLayout {
                    visible: root.setTab === "mnt"
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    spacing: 16

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 92
                        radius: 6
                        color: theme.pn
                        border.color: theme.amber
                        border.width: 1
                        Rectangle { width: 4; height: parent.height; color: theme.amber }
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 18
                            spacing: 6
                            Text { text: "Mode maintenance"; color: theme.amber; font.family: theme.sans; font.pixelSize: 18; font.weight: Font.Bold }
                            Text {
                                text: "La régulation automatique est suspendue. Les sorties sont pilotées manuellement. Réservé au personnel technique."
                                color: theme.mt; font.family: theme.sans; font.pixelSize: 14
                                wrapMode: Text.WordWrap
                                Layout.fillWidth: true
                            }
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 92
                        radius: 6
                        color: theme.amber
                        Text {
                            anchors.centerIn: parent
                            text: "ACTIVER LE MODE MAINTENANCE"
                            color: "#1a1204"
                            font.family: theme.sans
                            font.pixelSize: 22
                            font.weight: Font.Bold
                            font.letterSpacing: 1
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                frigo.commandMaintenanceMode(true);
                                root.enterMaintenance();
                            }
                        }
                    }

                    GridLayout {
                        Layout.fillWidth: true
                        columns: 2
                        columnSpacing: 12
                        rowSpacing: 12
                        Repeater {
                            model: [
                                { k: "Dernière intervention", v: "—" },
                                { k: "Version firmware", v: "—" }
                            ]
                            delegate: Rectangle {
                                required property var modelData
                                Layout.fillWidth: true
                                Layout.preferredHeight: 76
                                radius: 6
                                color: theme.pn
                                border.color: theme.ln
                                border.width: 1
                                ColumnLayout {
                                    anchors.fill: parent
                                    anchors.margins: 15
                                    spacing: 5
                                    Text { text: modelData.k; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.3 }
                                    Text { text: modelData.v; color: theme.tx; font.family: theme.mono; font.pixelSize: 20; font.weight: Font.DemiBold }
                                }
                            }
                        }
                    }
                }

                Item { Layout.preferredHeight: 12 }
            }
        }
    }
}
