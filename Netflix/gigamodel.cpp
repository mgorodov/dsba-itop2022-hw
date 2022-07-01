#include "gigamodel.h"

GigaModel::GigaModel(const std::vector<QString>& _data, const QString& _header, QObject* parent)
    : QAbstractTableModel { parent }
    , m_data(_data)
    , m_header(_header)
{
}

int GigaModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int GigaModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

Qt::ItemFlags GigaModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool GigaModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_data[index.row()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void GigaModel::setData(const std::vector<QString>& data)
{
    beginResetModel();
    m_data = data; // dangerous
    endResetModel();
    emit layoutChanged();
}

QVariant GigaModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_data[index.row()];
    return {};
}

QVariant GigaModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return m_header;
    return {};
}

void GigaModel::addRow()
{
    beginResetModel();
    m_data.push_back("");
    endResetModel();
    emit layoutChanged();
}

void GigaModel::deleteRows(const std::unordered_set<size_t>& selectedRows)
{
    beginResetModel();
    size_t j = 0;
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        if (selectedRows.find(i) == selectedRows.end())
            m_data[j++] = m_data[i];
    }
    m_data.resize(j);
    endResetModel();
    emit layoutChanged();
}

GigaFilter::GigaFilter(QObject* parent)
    : QSortFilterProxyModel { parent }
{
}

bool GigaFilter::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QVariant lhv = left.data(Qt::EditRole);
    QVariant rhv = right.data(Qt::EditRole);
    return lhv < rhv;
}

bool GigaFilter::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    return true;
}
