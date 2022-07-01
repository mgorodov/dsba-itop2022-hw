/*
       I believe It should be clear from naming, that this is definition of GigaModel class.
       It derives from QAbstractTableModel and used for providing acces to tables with one columns (e.g. genresList and languagesList)
*/

#pragma once
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <unordered_set>
class CustomDelegate;
class GigaSetter;
class GigaModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    GigaModel(const std::vector<QString>& _data, const QString& _header, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    void setData(const std::vector<QString>& data);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void addRow();
    void deleteRows(const std::unordered_set<size_t>& selectedRows);

private:
    std::vector<QString> m_data;
    QString m_header;
    friend class CustomDelegate;
    friend class GigaSetter;
};

class GigaFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    GigaFilter(QObject* parent = nullptr);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
};
