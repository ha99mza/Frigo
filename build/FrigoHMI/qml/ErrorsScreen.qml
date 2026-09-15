import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    color: "#0b1620"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Text {
                text: "Journal des erreurs"
                color: "#e8f0fa"
                font.pixelSize: 20
                font.bold: true
            }
            Item { Layout.fillWidth: true }
            Text {
                text: frigo.errorLog.activeCount + " active(s)"
                color: frigo.errorLog.activeCount > 0 ? "#ff5a5a" : "#8fa5c0"
                font.pixelSize: 14
            }
            Button {
                text: "Acquitter la plus récente"
                enabled: frigo.errorLog.activeCount > 0
                onClicked: frigo.errorLog.clearActive()
            }
            Button {
                text: "Effacer tout"
                onClicked: frigo.errorLog.clearAll()
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: frigo.errorLog
            spacing: 6

            delegate: Rectangle {
                width: ListView.view.width
                height: 60
                radius: 8
                color: model.active ? "#3a1616" : "#132338"
                border.color: model.active ? "#ff5a5a" : "#22415f"
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 14
                    anchors.rightMargin: 14
                    spacing: 14

                    Text {
                        text: "0x" + model.code.toString(16).padStart(2, "0")
                        color: model.active ? "#ff9d9d" : "#8fa5c0"
                        font.pixelSize: 15
                        font.family: "monospace"
                        Layout.preferredWidth: 60
                    }
                    Text {
                        text: model.description
                        color: "#e8f0fa"
                        font.pixelSize: 16
                        Layout.fillWidth: true
                    }
                    Text {
                        text: Qt.formatDateTime(model.timestamp, "dd/MM hh:mm:ss")
                        color: "#8fa5c0"
                        font.pixelSize: 13
                    }
                    Rectangle {
                        Layout.preferredWidth: 76
                        Layout.preferredHeight: 28
                        radius: 14
                        color: model.active ? "#8a1f1f" : "#1f3a5f"
                        Text {
                            anchors.centerIn: parent
                            text: model.active ? "ACTIVE" : "effacée"
                            color: "#ffffff"
                            font.pixelSize: 11
                        }
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                visible: parent.count === 0
                text: "Aucune erreur enregistrée"
                color: "#4c6d8c"
                font.pixelSize: 16
            }
        }
    }
}
