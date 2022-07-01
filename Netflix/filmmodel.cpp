#include "filmmodel.h"

inline const char* enumToString(FilmFields field)
{
    switch (field)
    {
    case FilmFields::title:
        return "Title";
    case FilmFields::imdb:
        return "IMDB Score";
    case FilmFields::premiere:
        return "Premiere";
    case FilmFields::runtime:
        return "Runtime";
    case FilmFields::genre:
        return "Genre";
    case FilmFields::language:
        return "Language";
    case FilmFields::COUNT:
        return "";
    }
    return {};
}

int FilmModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int FilmModel::columnCount(const QModelIndex& parent) const
{
    return static_cast<int>(FilmFields::COUNT);
}

void FilmModel::setData(const std::vector<Film>& data)
{
    beginResetModel();
    m_data = data; // dangerous
    endResetModel();
    emit layoutChanged();
}

Qt::ItemFlags FilmModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool FilmModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_data[index.row()].data[index.column()] = value.toString(); //List().join('/');
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void FilmModel::addRow()
{
    beginResetModel();
    m_data.push_back(Film());
    endResetModel();
    emit layoutChanged();
}

void FilmModel::deleteRows(const std::unordered_set<size_t>& selectedRows)
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

QVariant FilmModel::data(const QModelIndex& index, int role) const
{
    const Film& currentFilm = m_data[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return currentFilm.data[index.column()];
    return {};
}

QVariant FilmModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return enumToString(FilmFields(section));
    return {};
}
