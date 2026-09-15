import QtQuick
import QtQuick.Layouts
import QtQuick.Window

// Recreates the design's SVG temperature chart with a QML Canvas: grid,
// allowed-range band, filled area, and line — plus y/x axis label rails.
Item {
    id: root
    readonly property QtObject theme: Window.window.theme
    property var points: []       // [{t: unixSeconds, v: celsius}, ...] oldest-first
    property real bandMin: 0
    property real bandMax: 0
    property var xLabels: []      // 6 strings, oldest to newest

    readonly property real dataMin: points.length ? Math.min.apply(null, points.map(p => p.v)) : bandMin
    readonly property real dataMax: points.length ? Math.max.apply(null, points.map(p => p.v)) : bandMax
    readonly property real yTop: Math.max(bandMax + 1, dataMax + 0.5)
    readonly property real yBottom: Math.min(bandMin - 1, dataMin - 0.5)

    ColumnLayout {
        anchors.fill: parent
        spacing: 6

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 6

            Column {
                Layout.fillHeight: true
                Layout.preferredWidth: 28
                Repeater {
                    model: 6
                    delegate: Item {
                        required property int index
                        width: 28
                        height: (parent.height - 0) / 6
                        Text {
                            anchors.right: parent.right
                            anchors.top: parent.top
                            text: (root.yTop - (root.yTop - root.yBottom) * index / 5).toFixed(0)
                            font.family: theme.mono
                            font.pixelSize: 12
                            color: theme.mt
                        }
                    }
                }
            }

            Canvas {
                id: canvas
                Layout.fillWidth: true
                Layout.fillHeight: true
                antialiasing: true

                property var pts: root.points
                property real bMin: root.bandMin
                property real bMax: root.bandMax
                property real yTop: root.yTop
                property real yBot: root.yBottom
                property color lnColor: theme.ln
                property color accent: theme.accent

                onPtsChanged: requestPaint()
                onBMinChanged: requestPaint()
                onBMaxChanged: requestPaint()
                onLnColorChanged: requestPaint()
                onWidthChanged: requestPaint()
                onHeightChanged: requestPaint()
                // Property bindings don't fire their "Changed" signal on the
                // very first assignment (only on later changes), so without
                // this the chart stays blank until some property happens to
                // change after construction.
                Component.onCompleted: requestPaint()

                onPaint: {
                    const ctx = getContext("2d");
                    const w = width, h = height;
                    ctx.reset ? ctx.reset() : ctx.clearRect(0, 0, w, h);

                    ctx.strokeStyle = lnColor;
                    ctx.lineWidth = 1;
                    for (let i = 0; i <= 5; i++) {
                        const y = (h / 5) * i;
                        ctx.beginPath();
                        ctx.moveTo(0, y);
                        ctx.lineTo(w, y);
                        ctx.stroke();
                    }

                    const span = yTop - yBot;
                    if (span > 0) {
                        const bandY = ((yTop - bMax) / span) * h;
                        const bandH = ((bMax - bMin) / span) * h;
                        ctx.fillStyle = Qt.rgba(0.220, 0.741, 0.973, 0.09);
                        ctx.fillRect(0, bandY, w, bandH);
                    }

                    if (pts.length < 2 || span <= 0)
                        return;

                    const n = pts.length;
                    const xy = pts.map((p, i) => {
                        const x = (i / (n - 1)) * w;
                        let y = ((yTop - p.v) / span) * h;
                        y = Math.max(0, Math.min(h, y));
                        return [x, y];
                    });

                    ctx.fillStyle = Qt.rgba(0.220, 0.741, 0.973, 0.14);
                    ctx.beginPath();
                    ctx.moveTo(0, h);
                    for (const [x, y] of xy) ctx.lineTo(x, y);
                    ctx.lineTo(w, h);
                    ctx.closePath();
                    ctx.fill();

                    ctx.strokeStyle = accent;
                    ctx.lineWidth = 2.5;
                    ctx.lineJoin = "round";
                    ctx.beginPath();
                    ctx.moveTo(xy[0][0], xy[0][1]);
                    for (let i = 1; i < xy.length; i++) ctx.lineTo(xy[i][0], xy[i][1]);
                    ctx.stroke();
                }

                Text {
                    anchors.centerIn: parent
                    visible: root.points.length < 2
                    text: "Pas encore assez de données"
                    color: theme.mt
                    font.family: theme.sans
                    font.pixelSize: 14
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            Layout.leftMargin: 34

            Repeater {
                model: root.xLabels
                delegate: Text {
                    required property string modelData
                    required property int index
                    Layout.fillWidth: true
                    horizontalAlignment: index === 0 ? Text.AlignLeft
                                        : (index === root.xLabels.length - 1 ? Text.AlignRight : Text.AlignHCenter)
                    text: modelData
                    font.family: theme.mono
                    font.pixelSize: 12
                    color: theme.mt
                }
            }
        }
    }
}
