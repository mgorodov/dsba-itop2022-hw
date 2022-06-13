#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QVariant>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QLineEdit>

enum class FilmFields
{
    title, imdb, premiere, runtime, genre, language, COUNT
};

struct Film
{
    std::array<QVariant, static_cast<int> (FilmFields::COUNT)> data;
};

class FilmModel;
class FilterModel;

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
private:
    QLabel* appLabel = nullptr;
    QPushButton* addBtn = nullptr;
    QPushButton* delBtn = nullptr;
    QPushButton* uploadBtn = nullptr;
    QPushButton* saveBtn = nullptr;

    QLabel* filterLabel=nullptr;
    QLabel* filterIMDBFrom=nullptr;
    QLabel* filterIMDBTo=nullptr;
    QLabel* filterPremiereFrom=nullptr;
    QLabel* filterPremiereTo=nullptr;
    QLabel* filterRuntimeFrom=nullptr;
    QLabel* filterRuntimeTo=nullptr;
    QLabel* filterGenreLabel=nullptr;
    QLabel* filterLanguageLabel=nullptr;

    QLabel* titleLabel=nullptr;
    QLabel* imdbLabel=nullptr;
    QLabel* premiereLabel=nullptr;
    QLabel* runtimeLabel=nullptr;
    QLabel* genreLabel=nullptr;
    QLabel* languageLabel=nullptr;
    QLabel* detailsLabel=nullptr;

    QLineEdit* filterIMDBEditL=nullptr;
    QLineEdit* filterIMDBEditR=nullptr;
    QDateEdit* filterPremiereEditL=nullptr;
    QDateEdit* filterPremiereEditR=nullptr;
    QLineEdit* filterRuntimeEditL=nullptr;
    QLineEdit* filterRuntimeEditR=nullptr;
    QLineEdit* filterGenreEdit=nullptr;
    QLineEdit* filterLanguageEdit=nullptr;

    QLineEdit* titleEdit=nullptr;
    QLineEdit* imdbEdit=nullptr;
    QLineEdit* premiereEdit=nullptr;
    QLineEdit* runtimeEdit=nullptr;
    QLineEdit* genreEdit=nullptr;
    QLineEdit* languageEdit=nullptr;

    QModelIndex selectedCell;

    QTableView* masterView = nullptr;
    FilmModel* filmModel = nullptr;
    FilterModel* filterModel = nullptr;

    std::vector<Film> loadData(const QString &dir);
    void saveData(const QString &dir);
    void setupUI();
    void fileFailure();
public slots:
    void updateTitle(const QString& text);
    void updateIMDB(const QString& text);
    void updatePremiere(const QString& text);
    void updateRuntime(const QString& text);
    void updateGenre(const QString& text);
    void updateLanguage(const QString& text);
    void updateDetails(const QModelIndex &current, const QModelIndex &previous);
    void deleteRows();
    void addRows();
    void loadDataFunc();
    void saveDataFunc();
};

#include <iostream>
class FilmModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex &parent) const override
    {
        return m_data.size();
    }

    int columnCount(const QModelIndex &parent) const override
    {
        return static_cast<int> (FilmFields::COUNT);
    }

    void setData (const std::vector<Film> &data)
    {
        beginResetModel();
        m_data = data; // dangerous
        endResetModel();
        emit layoutChanged();
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (!index.isValid())
            return Qt::ItemIsEnabled;
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
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
        beginResetModel ();
        m_data.push_back (Film());
        endResetModel ();
        emit layoutChanged ();
    }

    void deleteRow(const QModelIndex &index)
    {
        beginResetModel ();
        m_data.erase(m_data.begin() + index.row());
        endResetModel();
        emit layoutChanged();
    }

    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
private:
    std::vector<Film> m_data;
    friend class MainPage;
};

class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    FilterModel (QObject *parent=nullptr,
                 QLineEdit* _filterIMDBEditL=nullptr,
                 QLineEdit* _filterIMDBEditR=nullptr,
                 QDateEdit* _filterPremiereEditL=nullptr,
                 QDateEdit* _filterPremiereEditR=nullptr,
                 QLineEdit* _filterRuntimeEditL=nullptr,
                 QLineEdit* _filterRuntimeEditR=nullptr,
                 QLineEdit* _filterGenreEdit=nullptr,
                 QLineEdit* _filterLanguageEdit=nullptr)
    {
        filterIMDBEditL =_filterIMDBEditL;
        filterIMDBEditR =_filterIMDBEditR;
        filterPremiereEditL =_filterPremiereEditL;
        filterPremiereEditR =_filterPremiereEditR;
        filterRuntimeEditL =_filterRuntimeEditL;
        filterRuntimeEditR =_filterRuntimeEditR;
        filterGenreEdit =_filterGenreEdit;
        filterLanguageEdit =_filterLanguageEdit;
    }
protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
private:
    QLineEdit* filterIMDBEditL=nullptr;
    QLineEdit* filterIMDBEditR=nullptr;
    QDateEdit* filterPremiereEditL=nullptr;
    QDateEdit* filterPremiereEditR=nullptr;
    QLineEdit* filterRuntimeEditL=nullptr;
    QLineEdit* filterRuntimeEditR=nullptr;
    QLineEdit* filterGenreEdit=nullptr;
    QLineEdit* filterLanguageEdit=nullptr;
};

#endif // MAINPAGE_H
