/***************************************************************************************************

  This file contains class FilmModel, which represents table-like data representation

***************************************************************************************************/

#pragma once

#include <QAbstractTableModel>
#include <unordered_set>
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
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    void setData(const std::vector<Film>& data);
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    void addRow();
    void deleteRows(const std::unordered_set<size_t>& selectedRows);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<Film> m_data;
    friend class MainPage;
};
