#include "errorlogmodel.h"
#include "canprotocol.h"

ErrorLogModel::ErrorLogModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ErrorLogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_entries.size();
}

QVariant ErrorLogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_entries.size())
        return {};

    const Entry &e = m_entries.at(index.row());
    switch (role) {
    case CodeRole:        return e.code;
    case DescriptionRole: return CanProtocol::errorCodeToString(e.code);
    case TimestampRole:   return e.timestamp;
    case ActiveRole:      return e.active;
    default:              return {};
    }
}

QHash<int, QByteArray> ErrorLogModel::roleNames() const
{
    return {
        { CodeRole, "code" },
        { DescriptionRole, "description" },
        { TimestampRole, "timestamp" },
        { ActiveRole, "active" },
    };
}

void ErrorLogModel::addError(quint8 code)
{
    if (code == CanProtocol::Err_None)
        return;

    // Avoid spamming the log if the same error keeps repeating while active.
    if (!m_entries.isEmpty() && m_entries.first().code == code && m_entries.first().active)
        return;

    beginInsertRows(QModelIndex(), 0, 0);
    m_entries.prepend(Entry{ code, QDateTime::currentDateTime(), true });
    endInsertRows();
    emit activeCountChanged();
}

void ErrorLogModel::clearActive()
{
    for (int i = 0; i < m_entries.size(); ++i) {
        if (m_entries[i].active) {
            m_entries[i].active = false;
            const QModelIndex idx = index(i);
            emit dataChanged(idx, idx, { ActiveRole });
            emit activeCountChanged();
            return; // only the most recent active entry
        }
    }
}

void ErrorLogModel::clearAllActive()
{
    bool changed = false;
    for (int i = 0; i < m_entries.size(); ++i) {
        if (m_entries[i].active) {
            m_entries[i].active = false;
            const QModelIndex idx = index(i);
            emit dataChanged(idx, idx, { ActiveRole });
            changed = true;
        }
    }
    if (changed)
        emit activeCountChanged();
}

void ErrorLogModel::clearActiveByCode(quint8 code)
{
    bool changed = false;
    for (int i = 0; i < m_entries.size(); ++i) {
        if (m_entries[i].active && m_entries[i].code == code) {
            m_entries[i].active = false;
            const QModelIndex idx = index(i);
            emit dataChanged(idx, idx, { ActiveRole });
            changed = true;
        }
    }
    if (changed)
        emit activeCountChanged();
}

void ErrorLogModel::clearAll()
{
    if (m_entries.isEmpty())
        return;
    beginResetModel();
    m_entries.clear();
    endResetModel();
    emit activeCountChanged();
}

QString ErrorLogModel::topActiveSummary() const
{
    for (const Entry &e : m_entries) {
        if (e.active)
            return CanProtocol::errorCodeToString(e.code) + QStringLiteral(" — ") + e.timestamp.toString(QStringLiteral("hh:mm:ss"));
    }
    return QString();
}

int ErrorLogModel::activeCount() const
{
    int n = 0;
    for (const Entry &e : m_entries)
        if (e.active)
            ++n;
    return n;
}
