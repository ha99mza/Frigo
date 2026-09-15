#pragma once

#include <QAbstractListModel>
#include <QDateTime>
#include <QVector>

// List model backing the "Erreurs" screen: one row per error event received
// on CAN id 0x001, newest first.
class ErrorLogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        CodeRole = Qt::UserRole + 1,
        DescriptionRole,
        TimestampRole,
        ActiveRole,
    };
    Q_ENUM(Roles)

    explicit ErrorLogModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Adds a new entry unless it's a duplicate of the currently-active error.
    Q_INVOKABLE void addError(quint8 code);
    // Marks the most recent active error as cleared (generic "dismiss" action).
    Q_INVOKABLE void clearActive();
    // Marks all active errors matching a given code as cleared (e.g. board
    // reports the door-open alarm was stopped: only clear door errors).
    Q_INVOKABLE void clearActiveByCode(quint8 code);
    // Marks every active entry as cleared (bulk "acquitter tout").
    Q_INVOKABLE void clearAllActive();
    Q_INVOKABLE void clearAll();

    Q_PROPERTY(int activeCount READ activeCount NOTIFY activeCountChanged)
    int activeCount() const;

    // Description of the most recent active entry (for the top alarm
    // banner), or empty when nothing is active.
    Q_PROPERTY(QString topActiveSummary READ topActiveSummary NOTIFY activeCountChanged)
    QString topActiveSummary() const;

signals:
    void activeCountChanged();

private:
    struct Entry {
        quint8 code;
        QDateTime timestamp;
        bool active;
    };
    QVector<Entry> m_entries;
};
