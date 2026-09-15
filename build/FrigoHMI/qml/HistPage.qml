import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import "components"

Item {
    id: root
    readonly property QtObject theme: Window.window.theme
    property string range: "24h"

    readonly property var xLabelSets: ({
        "1h": ["-60m", "-48m", "-36m", "-24m", "-12m", "now"],
        "24h": ["-24h", "-19h", "-14h", "-10h", "-5h", "now"],
        "7j": ["J-7", "J-6", "J-4", "J-3", "J-2", "auj."]
    })

    property var series: []
    property var stats: ({ count: 0, min: 0, max: 0, avg: 0, defrostCount: 0 })

    function refresh() {
        series = frigo.temperatureSeries(range);
        stats = frigo.rangeStats(range);
    }

    onRangeChanged: refresh()
    Component.onCompleted: refresh()
    Timer { interval: 15000; running: true; repeat: true; onTriggered: root.refresh() }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: 14

        RowLayout {
            Layout.fillWidth: true
            spacing: 14

            Text {
                text: "HISTORIQUE TEMPÉRATURE"
                color: theme.mt
                font.family: theme.sans
                font.pixelSize: 14
                font.weight: Font.DemiBold
                font.letterSpacing: 2
            }
            Item { Layout.fillWidth: true }

            RowLayout {
                spacing: 8
                Repeater {
                    model: ["1h", "24h", "7j"]
                    delegate: Rectangle {
                        required property string modelData
                        readonly property bool on: root.range === modelData
                        width: 92; height: 52
                        radius: 5
                        color: theme.selBgFor(on)
                        border.color: on ? theme.accent : theme.ln
                        border.width: 1
                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            font.pixelSize: 17
                            font.weight: Font.DemiBold
                            font.family: theme.sans
                            color: theme.selColor(on)
                        }
                        MouseArea { anchors.fill: parent; onClicked: root.range = modelData }
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 6
            color: theme.pn
            border.color: theme.ln
            border.width: 1

            TempChart {
                anchors.fill: parent
                anchors.margins: 14
                anchors.topMargin: 10
                points: root.series
                bandMin: frigo.tempMinC
                bandMax: frigo.tempMaxC
                xLabels: root.xLabelSets[root.range]
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 92
            Layout.maximumHeight: 92
            spacing: 12

            Repeater {
                model: [
                    { k: "Minimum", v: root.stats.count ? root.stats.min.toFixed(1) + " °C" : "—" },
                    { k: "Maximum", v: root.stats.count ? root.stats.max.toFixed(1) + " °C" : "—" },
                    { k: "Moyenne", v: root.stats.count ? root.stats.avg.toFixed(1) + " °C" : "—" },
                    { k: "Dégivrages", v: String(root.stats.defrostCount) }
                ]
                delegate: Rectangle {
                    required property var modelData
                    Layout.fillWidth: true
                    Layout.preferredHeight: 92
                    Layout.maximumHeight: 92
                    radius: 6
                    color: theme.pn
                    border.color: theme.ln
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 14
                        spacing: 4
                        Text { text: modelData.k; color: theme.mt; font.family: theme.sans; font.pixelSize: 12; font.letterSpacing: 1.3 }
                        Text { text: modelData.v; color: theme.tx; font.family: theme.mono; font.pixelSize: 28; font.weight: Font.DemiBold }
                    }
                }
            }
        }
    }
}
