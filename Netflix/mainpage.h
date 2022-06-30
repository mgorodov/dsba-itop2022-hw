/***************************************************************************************************

  Primary window of the application, where user can load/save/add/edit data as well as enable
  filters and sorting

***************************************************************************************************/

#pragma once

#include "customdelegate.h"
#include "filmmodel.h"
#include "filtermodel.h"
#include "genresetter.h"
#include "genresmodel.h"
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <fstream>
#include <sstream>
#include <unordered_set>

class MainPage : public QWidget
{
    Q_OBJECT
public:
    MainPage(QWidget* parent = nullptr);
    ~MainPage() override;

private:
    QLabel* appLabel = nullptr;
    QPushButton* addBtn = nullptr;
    QPushButton* delBtn = nullptr;
    QPushButton* uploadBtn = nullptr;
    QPushButton* saveBtn = nullptr;

    QLabel* filterLabel = nullptr;
    QLabel* filterIMDBFrom = nullptr;
    QLabel* filterIMDBTo = nullptr;
    QLabel* filterPremiereFrom = nullptr;
    QLabel* filterPremiereTo = nullptr;
    QLabel* filterRuntimeFrom = nullptr;
    QLabel* filterRuntimeTo = nullptr;
    QLabel* filterGenreLabel = nullptr;
    QLabel* filterLanguageLabel = nullptr;

    QLabel* titleLabel = nullptr;
    QLabel* imdbLabel = nullptr;
    QLabel* premiereLabel = nullptr;
    QLabel* runtimeLabel = nullptr;
    QLabel* genreLabel = nullptr;
    QLabel* languageLabel = nullptr;
    QLabel* detailsLabel = nullptr;

    QLineEdit* filterIMDBEditL = nullptr;
    QLineEdit* filterIMDBEditR = nullptr;
    QDateEdit* filterPremiereEditL = nullptr;
    QDateEdit* filterPremiereEditR = nullptr;
    QLineEdit* filterRuntimeEditL = nullptr;
    QLineEdit* filterRuntimeEditR = nullptr;
    QLineEdit* filterGenreEdit = nullptr;
    QLineEdit* filterLanguageEdit = nullptr;
    QPushButton* genreSetterBtn = nullptr;

    QLineEdit* titleEdit = nullptr;
    QLineEdit* imdbEdit = nullptr;
    QLineEdit* premiereEdit = nullptr;
    QLineEdit* runtimeEdit = nullptr;
    QLineEdit* genreEdit = nullptr;
    QLineEdit* languageEdit = nullptr;

    QModelIndex selectedCell;

    QTableView* masterView = nullptr;
    FilmModel* filmModel = nullptr;
    FilterModel* filterModel = nullptr;
    CustomDelegate* customDelegate = nullptr;
    GenreSetter* genreSetter = nullptr;
    GenresModel* genresModel = nullptr;

    std::vector<Film> loadData(const QString& dir);
    void saveData(const QString& dir);
    void setupUI();
    void fileFailure();
public slots:
    void updateTitle(const QString& text);
    void updateIMDB(const QString& text);
    void updatePremiere(const QString& text);
    void updateRuntime(const QString& text);
    void updateGenre(const QString& text);
    void updateLanguage(const QString& text);
    void updateDetails(const QModelIndex& current, const QModelIndex& previous);
    void deleteRows();
    void addRows();
    void loadDataFunc();
    void saveDataFunc();
    void openGenreSetter();
};
