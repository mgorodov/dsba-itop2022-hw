#include "genresmodel.h"

GenresModel::GenresModel(QObject* parent)
    : QAbstractTableModel { parent }
    , m_data {
        "Action",
        "Action comedy",
        "Action adventure",
        "Adventure",
        "Aftershow",
        "Animation",
        "Anime",
        "Anthology",
        "Biopic",
        "Black comedy",
        "Christmas",
        "Christmas musical",
        "Comedy",
        "Coming-of-age comedy-drama",
        "Crime drama",
        "Documentary",
        "Drama",
        "Family",
        "Horror",
        "Historical-epic",
        "Mentalism special",
        "Musical",
        "Musical comedy",
        "One-man show",
        "Political thriller",
        "Psychological thriller",
        "Romance",
        "Romantic comedy",
        "Romantic drama",
        "Satire",
        "Science fiction",
        "Sports drama",
        "Spy thriller",
        "Superhero",
        "Supernatural drama",
        "Teen comedy horror",
        "Thriller",
        "Urban fantasy",
        "Variety show",
        "War",
        "Western",
        "Zombie"
    }
{
}

int GenresModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int GenresModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

Qt::ItemFlags GenresModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool GenresModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_data[index.row()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant GenresModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_data[index.row()];
    return {};
}

QVariant GenresModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return "Genres";
    return {};
}

void GenresModel::addRow()
{
    beginResetModel();
    m_data.push_back("");
    endResetModel();
    emit layoutChanged();
}

void GenresModel::deleteRows(const std::unordered_set<size_t>& selectedRows)
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

GenresFilter::GenresFilter(QObject* parent)
    : QSortFilterProxyModel { parent }
{
}

bool GenresFilter::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QVariant lhv = left.data(Qt::EditRole);
    QVariant rhv = right.data(Qt::EditRole);
    return lhv < rhv;
}

bool GenresFilter::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    return true;
}
