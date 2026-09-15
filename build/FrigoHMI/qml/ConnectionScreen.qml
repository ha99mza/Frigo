import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#0b1620"

    function refreshInterfaces() {
        socketcanCombo.model = frigo.availableInterfaces("socketcan")
        peakcanCombo.model = frigo.availableInterfaces("peakcan")
    }

    Component.onCompleted: refreshInterfaces()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        Text {
            text: "Connexion CAN"
            color: "#e8f0fa"
            font.pixelSize: 22
            font.bold: true
        }

        RowLayout {
            spacing: 10
            Rectangle {
                width: 12; height: 12; radius: 6
                color: frigo.connected ? "#3ecf7d" : "#ff5a5a"
            }
            Text {
                text: frigo.connected ? ("Connecté — " + frigo.backendLabel) : "Déconnecté"
                color: "#e8f0fa"
                font.pixelSize: 16
            }
            Button {
                text: "Déconnecter"
                enabled: frigo.connected
                onClicked: frigo.disconnectCan()
            }
        }

        Rectangle { Layout.fillWidth: true; height: 1; color: "#22354a" }

        // --- Linux: SocketCAN ------------------------------------------
        ColumnLayout {
            spacing: 8
            Text { text: "Linux — SocketCAN"; color: "#8fa5c0"; font.pixelSize: 14 }
            RowLayout {
                spacing: 10
                ComboBox {
                    id: socketcanCombo
                    Layout.preferredWidth: 220
                    editable: true
                    model: []
                }
                Button {
                    text: "Connecter (SocketCAN)"
                    onClicked: frigo.connectSocketCan(socketcanCombo.editText.length > 0
                                                        ? socketcanCombo.editText : "can0")
                }
                Button {
                    text: "⟳"
                    implicitWidth: 44
                    onClicked: root.refreshInterfaces()
                }
            }
        }

        // --- Windows: PEAK PCAN-USB --------------------------------------
        ColumnLayout {
            spacing: 8
            Text { text: "Windows — PEAK PCAN-USB"; color: "#8fa5c0"; font.pixelSize: 14 }
            RowLayout {
                spacing: 10
                ComboBox {
                    id: peakcanCombo
                    Layout.preferredWidth: 220
                    editable: true
                    model: []
                }
                Button {
                    text: "Connecter (PCAN-USB)"
                    onClicked: frigo.connectPeakCan(peakcanCombo.editText.length > 0
                                                     ? peakcanCombo.editText : "usb0")
                }
            }
        }

        // --- Simulator ----------------------------------------------------
        ColumnLayout {
            spacing: 8
            Text { text: "Sans matériel"; color: "#8fa5c0"; font.pixelSize: 14 }
            Button {
                text: "Connecter le simulateur"
                onClicked: frigo.connectSimulator()
            }
        }

        Item { Layout.fillHeight: true }

        Text {
            text: frigo.lastError.length > 0 ? ("Dernière erreur : " + frigo.lastError) : ""
            color: "#ff9d9d"
            font.pixelSize: 13
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }
    }
}
