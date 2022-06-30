#pragma once
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <unordered_set>
class CustomDelegate;
class GenreSetter;
class GenresModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    GenresModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void addRow();
    void deleteRows(const std::unordered_set<size_t>& selectedRows);

private:
    std::vector<QString> m_data;
    friend class CustomDelegate;
    friend class GenreSetter;
};

class GenresFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    GenresFilter(QObject* parent = nullptr);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
};
