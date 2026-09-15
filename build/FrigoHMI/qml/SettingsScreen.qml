import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "components"

Rectangle {
    color: "#0b1620"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Button {
                text: "Lire depuis la carte"
                onClicked: frigo.requestConfigFromBoard()
            }
            Button {
                text: "Envoyer à la carte"
                enabled: frigo.connected
                highlighted: frigo.configDirty
                onClicked: frigo.writeConfigToBoard()
            }
            Item { Layout.fillWidth: true }

            Text {
                color: frigo.configDirty ? "#e0a83e" : (frigo.configSynced ? "#3ecf7d" : "#8fa5c0")
                font.pixelSize: 13
                text: frigo.configDirty
                      ? "Modifications non envoyées"
                      : (frigo.configSynced ? "Synchronisé avec la carte" : "Signature non vérifiée")
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ColumnLayout {
                width: parent.width
                spacing: 8

                SettingRow {
                    Layout.fillWidth: true
                    label: "Température minimale"; unit: "°C"
                    from: -50; to: 50; stepSize: 0.5; decimals: 1
                    value: frigo.tempMinC
                    onValueModified: (v) => frigo.tempMinC = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Température maximale"; unit: "°C"
                    from: -50; to: 50; stepSize: 0.5; decimals: 1
                    value: frigo.tempMaxC
                    onValueModified: (v) => frigo.tempMaxC = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Température évaporateur min."; unit: "°C"
                    from: -50; to: 50; stepSize: 0.5; decimals: 1
                    value: frigo.tempEvaMinC
                    onValueModified: (v) => frigo.tempEvaMinC = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Intervalle dégivrage"; unit: "h"
                    from: 0; to: 48; stepSize: 0.5; decimals: 1
                    value: frigo.defrostIntervalHours
                    onValueModified: (v) => frigo.defrostIntervalHours = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Durée dégivrage"; unit: "min"
                    from: 0; to: 120; stepSize: 1; decimals: 0
                    value: frigo.defrostDurationMinutes
                    onValueModified: (v) => frigo.defrostDurationMinutes = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Timeout dégivrage"; unit: "min"
                    from: 0; to: 180; stepSize: 1; decimals: 0
                    value: frigo.defrostTimeoutMinutes
                    onValueModified: (v) => frigo.defrostTimeoutMinutes = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Anti-court cycle"; unit: "s"
                    from: 0; to: 1800; stepSize: 10; decimals: 0
                    value: frigo.antiShortCycleDelaySeconds
                    onValueModified: (v) => frigo.antiShortCycleDelaySeconds = Math.round(v)
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Timeout limite température"; unit: "s"
                    from: 0; to: 7200; stepSize: 30; decimals: 0
                    value: frigo.tempLimitTimeoutSeconds
                    onValueModified: (v) => frigo.tempLimitTimeoutSeconds = Math.round(v)
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Alarme porte ouverte"; unit: "min"
                    from: 0; to: 60; stepSize: 1; decimals: 0
                    value: frigo.doorAlarmDelayMinutes
                    onValueModified: (v) => frigo.doorAlarmDelayMinutes = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Offset capteur 1"; unit: "°C"
                    from: -10; to: 10; stepSize: 0.1; decimals: 1
                    value: frigo.offsetCap1C
                    onValueModified: (v) => frigo.offsetCap1C = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Offset capteur 2"; unit: "°C"
                    from: -10; to: 10; stepSize: 0.1; decimals: 1
                    value: frigo.offsetCap2C
                    onValueModified: (v) => frigo.offsetCap2C = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Offset capteur 3"; unit: "°C"
                    from: -10; to: 10; stepSize: 0.1; decimals: 1
                    value: frigo.offsetCap3C
                    onValueModified: (v) => frigo.offsetCap3C = v
                }
                SettingRow {
                    Layout.fillWidth: true
                    label: "Offset évaporateur"; unit: "°C"
                    from: -10; to: 10; stepSize: 0.1; decimals: 1
                    value: frigo.offsetEvaC
                    onValueModified: (v) => frigo.offsetEvaC = v
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 56
                    spacing: 12

                    Text {
                        text: "Mode maintenance"
                        color: "#e8f0fa"
                        font.pixelSize: 16
                        Layout.preferredWidth: 340
                    }
                    Switch {
                        checked: frigo.maintenanceMode
                        onToggled: frigo.maintenanceMode = checked
                    }
                }

                Text {
                    Layout.topMargin: 8
                    Layout.bottomMargin: 16
                    color: "#8fa5c0"
                    text: "Signature locale: 0x" + frigo.localSignature.toString(16)
                          + "   Signature carte: 0x" + frigo.boardSignature.toString(16)
                    font.pixelSize: 12
                }
            }
        }
    }
}
