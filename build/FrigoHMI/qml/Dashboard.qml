import QtQuick
import QtQuick.Layouts
import "components"

Rectangle {
    color: "#0b1620"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 190
            spacing: 20

            TempGauge {
                Layout.preferredWidth: 260
                Layout.fillHeight: true
                big: true
                label: "Température moyenne"
                value: frigo.tempAverage
                warnLow: frigo.tempMinC - 100
                warnHigh: frigo.tempMaxC
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 4
                rowSpacing: 12
                columnSpacing: 12

                TempGauge { Layout.fillWidth: true; Layout.fillHeight: true; label: "Capteur 1"; value: frigo.temp1 }
                TempGauge { Layout.fillWidth: true; Layout.fillHeight: true; label: "Capteur 2"; value: frigo.temp2 }
                TempGauge { Layout.fillWidth: true; Layout.fillHeight: true; label: "Capteur 3"; value: frigo.temp3 }
                TempGauge { Layout.fillWidth: true; Layout.fillHeight: true; label: "Évaporateur"; value: frigo.tempEva; warnHigh: frigo.tempEvaMinC + 200 }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            StatusPill {
                label: "Porte"
                active: frigo.doorOpen
                activeText: "Ouverte"
                inactiveText: "Fermée"
            }
            StatusPill {
                label: "Batterie"
                active: frigo.batteryVoltage < 11.5
                activeColor: "#ff5a5a"
                activeText: frigo.batteryVoltage.toFixed(2) + " V (faible)"
                inactiveText: frigo.batteryVoltage.toFixed(2) + " V"
            }
            StatusPill {
                label: "Maintenance"
                active: frigo.maintenanceMode
                activeColor: "#e0a83e"
                activeText: "Activée"
                inactiveText: "Désactivée"
            }
            Item { Layout.fillWidth: true }
        }

        Rectangle { Layout.fillWidth: true; height: 1; color: "#22354a" }

        Text {
            text: "Sorties relais"
            color: "#8fa5c0"
            font.pixelSize: 14
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 88
            spacing: 10

            RelayIndicator { label: "Vent. 1"; iconGlyph: "🌀"; on: frigo.fan1On }
            RelayIndicator { label: "Vent. 2"; iconGlyph: "🌀"; on: frigo.fan2On }
            RelayIndicator { label: "Vent. 3"; iconGlyph: "🌀"; on: frigo.fan3On }
            RelayIndicator { label: "Vent. 4"; iconGlyph: "🌀"; on: frigo.fan4On }
            RelayIndicator { label: "Vent. 5"; iconGlyph: "🌀"; on: frigo.fan5On }
            RelayIndicator { label: "Lampe"; iconGlyph: "💡"; on: frigo.lampOn }
            RelayIndicator { label: "Compr."; iconGlyph: "🧊"; on: frigo.compressorOn }
            RelayIndicator { label: "Dégivr."; iconGlyph: "♨"; on: frigo.defrostFanOn }
            RelayIndicator { label: "Rel. porte"; iconGlyph: "🚪"; on: frigo.doorRelayOn }
            Item { Layout.fillWidth: true }
        }
    }
}
