/***************************************************************************************************

  This file contains class FilmModel, which represents table-like data representation

***************************************************************************************************/

#pragma once

#include <QAbstractTableModel>

enum class FilmFields
{
    title,
    imdb,
    premiere,
    runtime,
    genre,
    language,
    COUNT
};

struct Film
{
    std::array<QVariant, static_cast<int>(FilmFields::COUNT)> data;
};

class FilmModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex& parent) const override
    {
        return m_data.size();
    }

    int columnCount(const QModelIndex& parent) const override
    {
        return static_cast<int>(FilmFields::COUNT);
    }

    void setData(const std::vector<Film>& data)
    {
        beginResetModel();
        m_data = data; // dangerous
        endResetModel();
        emit layoutChanged();
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        if (!index.isValid())
            return Qt::ItemIsEnabled;
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role) override
    {
        if (index.isValid() && role == Qt::EditRole)
        {
            m_data[index.row()].data[index.column()] = value.toString();
            emit dataChanged(index, index);
            return true;
        }
        return false;
    }

    void addRow()
    {
        beginResetModel();
        m_data.push_back(Film());
        endResetModel();
        emit layoutChanged();
    }

    void deleteRow(const QModelIndex& index)
    {
        beginResetModel();
        m_data.erase(m_data.begin() + index.row());
        endResetModel();
        emit layoutChanged();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<Film> m_data;
    friend class MainPage;
};
