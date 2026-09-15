#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>

// Lightweight append-only local history for the Historique page: temperature
// samples and defrost-cycle start events, persisted as plain text log files
// under the app's data directory so 24h/7j charts survive restarts. Not a
// database — just enough to answer "give me everything from the last N
// seconds" without pulling in QtSql for a couple of small rolling logs.
class HistoryStore : public QObject
{
    Q_OBJECT
public:
    explicit HistoryStore(QObject *parent = nullptr);

    // Records the current chamber average temperature (°C). Caller is
    // expected to throttle calls (e.g. once per minute) — this appends
    // unconditionally.
    void addTempSample(double celsius);

    // Records a defrost-cycle start (call on the defrost relay's off->on edge).
    void addDefrostEvent();

    // range: "1h", "24h", or "7j". Returns [{t: <unix seconds>, v: <°C>}, ...]
    // ordered oldest-first, restricted to the window.
    Q_INVOKABLE QVariantList temperatureSeries(const QString &range) const;

    // Returns {min, max, avg, defrostCount} over the same window. Values are
    // 0 when there is no data yet (check count==0 via an empty series first).
    Q_INVOKABLE QVariantMap rangeStats(const QString &range) const;

    // Unix timestamp of the most recent defrost-cycle start, or 0 if none
    // recorded (within the retention window).
    Q_INVOKABLE qint64 lastDefrostEvent() const { return m_defrostEvents.isEmpty() ? 0 : m_defrostEvents.last(); }

private:
    struct TempSample { qint64 t; double v; };

    static qint64 windowSeconds(const QString &range);
    void loadAndPrune();
    void pruneToFile(const QString &path, qint64 cutoff);

    QString m_tempLogPath;
    QString m_defrostLogPath;
    QVector<TempSample> m_tempSamples;
    QVector<qint64> m_defrostEvents;
};
