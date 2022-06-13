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
