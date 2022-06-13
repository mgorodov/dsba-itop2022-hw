#include "mainpage.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QScrollBar>
#include <fstream>
#include <sstream>
#include <iostream>

MainPage::MainPage(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
    connect(addBtn, SIGNAL(clicked()), SLOT(addRows()));
    connect(delBtn, SIGNAL(clicked()), SLOT(deleteRows()));
    connect(uploadBtn, SIGNAL(clicked()), SLOT(loadDataFunc()));
    connect(saveBtn, SIGNAL(clicked()), SLOT(saveDataFunc()));
    connect(masterView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(updateDetails(QModelIndex,QModelIndex)));

    connect(titleEdit, SIGNAL(textChanged(QString)), this, SLOT(updateTitle(QString)));
    connect(imdbEdit, SIGNAL(textChanged(QString)), this, SLOT(updateIMDB(QString)));
    connect(premiereEdit, SIGNAL(textChanged(QString)), this, SLOT(updatePremiere(QString)));
    connect(runtimeEdit, SIGNAL(textChanged(QString)), this, SLOT(updateRuntime(QString)));
    connect(genreEdit, SIGNAL(textChanged(QString)), this, SLOT(updateGenre(QString)));
    connect(languageEdit, SIGNAL(textChanged(QString)), this, SLOT(updateLanguage(QString)));

    connect(filterIMDBEditL, SIGNAL(textChanged(QString)), filterModel, SLOT(invalidate()));
    connect(filterIMDBEditR, SIGNAL(textChanged(QString)), filterModel, SLOT(invalidate()));
    connect(filterPremiereEditL, SIGNAL(dateChanged(QDate)), filterModel, SLOT(invalidate()));
    connect(filterPremiereEditR, SIGNAL(dateChanged(QDate)), filterModel, SLOT(invalidate()));
    connect(filterRuntimeEditL, SIGNAL(textChanged(QString)), filterModel, SLOT(invalidate()));
    connect(filterRuntimeEditR, SIGNAL(textChanged(QString)), filterModel, SLOT(invalidate()));
    connect(filterGenreEdit, SIGNAL(textChanged(QString)), filterModel, SLOT(invalidate()));
    connect(filterLanguageEdit, SIGNAL(textChanged(QString)), filterModel, SLOT(invalidate()));
}

void MainPage::setupUI()
{
    resize(1500, 800);

    appLabel = new QLabel("Netflix reviews");
    appLabel->setFont(QFont("Montserrat", 30));
    appLabel->setStyleSheet("background-color: #24252A; color: #FFFFFF; padding: 15; border-bottom: 1px solid #FFFFFF");

    addBtn = new QPushButton("ADD");
    delBtn = new QPushButton("DEL");
    uploadBtn = new QPushButton;
    saveBtn = new QPushButton;

    addBtn->setFont(QFont("Montserrat", 25));
    addBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                           "QPushButton:hover{background-color: #1199BA;}");
    delBtn->setFont(QFont("Montserrat", 25));
    delBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                           "QPushButton:hover{background-color: #1199BA;}");

    uploadBtn->setIcon(QIcon(QPixmap(":/upload.ico")));
    uploadBtn->setIconSize(QSize(45, 45));
    uploadBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                           "QPushButton:hover{background-color: #1199BA;}");

    saveBtn->setIcon(QIcon(QPixmap(":/download.ico")));
    saveBtn->setIconSize(QSize(45, 45));
    saveBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                           "QPushButton:hover{background-color: #1199BA;}");

    QHBoxLayout *actLayout = new QHBoxLayout;
    actLayout->addWidget(addBtn);
    actLayout->addWidget(delBtn);
    actLayout->addWidget(uploadBtn);
    actLayout->addWidget(saveBtn);

    QGroupBox *actions = new QGroupBox;
    actions->setLayout(actLayout);
    actions->setStyleSheet("QGroupBox{background-color: #24252A; border-top: 1px solid #FFFFFF;}");

    filterLabel = new QLabel("Filters");
    filterLabel->setAlignment(Qt::AlignCenter);
    filterIMDBFrom = new QLabel("IMDB from ");
    filterPremiereFrom = new QLabel("Premiere from ");
    filterRuntimeFrom = new QLabel("Runtime from ");
    filterIMDBTo = new QLabel(" to ");
    filterPremiereTo = new QLabel(" to ");
    filterRuntimeTo = new QLabel(" to ");
    filterGenreLabel = new QLabel("Genre ");
    filterLanguageLabel = new QLabel("Language ");

    filterIMDBEditL = new QLineEdit("");
    filterIMDBEditR = new QLineEdit("");
    filterPremiereEditL = new QDateEdit(QDate(1800, 1, 1));
    filterPremiereEditR = new QDateEdit(QDate(2022, 1, 1));
    filterRuntimeEditL = new QLineEdit("");
    filterRuntimeEditR = new QLineEdit("");
    filterGenreEdit = new QLineEdit("");
    filterLanguageEdit = new QLineEdit("");

    detailsLabel = new QLabel("Details");
    titleLabel = new QLabel("Title");
    imdbLabel = new QLabel("IMDB Score");
    premiereLabel = new QLabel("Premiere");
    runtimeLabel = new QLabel("Runtime");
    genreLabel = new QLabel("Genre");
    languageLabel = new QLabel("Language");

    titleEdit = new QLineEdit("");
    imdbEdit = new QLineEdit("");
    premiereEdit = new QLineEdit("");
    runtimeEdit = new QLineEdit("");
    genreEdit = new QLineEdit("");
    languageEdit = new QLineEdit("");

    QGridLayout *details = new QGridLayout;
    details->setContentsMargins(0, 0, 0, 0);
    details->addWidget(filterLabel, 0, 0, 1, 4, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterIMDBFrom, 1, 0, Qt::AlignTop);
    details->addWidget(filterIMDBEditL, 1, 1, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterIMDBTo, 1, 2, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterIMDBEditR, 1, 3, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterPremiereFrom, 2, 0, Qt::AlignTop);
    details->addWidget(filterPremiereEditL, 2, 1, Qt::AlignTop);
    details->addWidget(filterPremiereTo, 2, 2, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterPremiereEditR, 2, 3, Qt::AlignTop);
    details->addWidget(filterRuntimeFrom, 3, 0, Qt::AlignTop);
    details->addWidget(filterRuntimeEditL, 3, 1, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterRuntimeTo, 3, 2, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterRuntimeEditR, 3, 3, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterGenreLabel, 4, 0, Qt::AlignTop);
    details->addWidget(filterGenreEdit, 4, 1, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(filterLanguageLabel, 5, 0, Qt::AlignTop);
    details->addWidget(filterLanguageEdit, 5, 1, Qt::AlignTop|Qt::AlignHCenter);
    details->addWidget(detailsLabel, 6, 0, 1, 4, Qt::AlignBottom|Qt::AlignHCenter);
    details->addWidget(titleLabel, 7, 0, Qt::AlignBottom);
    details->addWidget(titleEdit, 7, 1, 1, 3, Qt::AlignBottom);
    details->addWidget(imdbLabel, 8, 0, Qt::AlignBottom);
    details->addWidget(imdbEdit, 8, 1, 1, 3, Qt::AlignBottom);
    details->addWidget(premiereLabel, 9, 0, Qt::AlignBottom);
    details->addWidget(premiereEdit, 9, 1, 1, 3, Qt::AlignBottom);
    details->addWidget(runtimeLabel, 10, 0, Qt::AlignBottom);
    details->addWidget(runtimeEdit, 10, 1, 1, 3, Qt::AlignBottom);
    details->addWidget(genreLabel, 11, 0, Qt::AlignBottom);
    details->addWidget(genreEdit, 11, 1, 1, 3, Qt::AlignBottom);
    details->addWidget(languageLabel, 12, 0, Qt::AlignBottom);
    details->addWidget(languageEdit, 12, 1, 1, 3, Qt::AlignBottom);

    QGroupBox *detailsBox = new QGroupBox;
    detailsBox->setLayout(details);
    detailsBox->setStyleSheet("QGroupBox{padding: 10 10;}"
                              "QGroupBox QLabel{font-size: 30px;}"
                              "QGroupBox QLineEdit{font-size: 30px;}"
                              "QGroupBox QDateEdit{font-size: 30px;}");

    filterLabel->setStyleSheet("font-weight: 500; font-size 35px;");
    detailsLabel->setStyleSheet("font-weight: 500; font-size 35px;");

    filmModel = new FilmModel;
    filterModel = new FilterModel(nullptr,
                                  filterIMDBEditL,
                                  filterIMDBEditR,
                                  filterPremiereEditL,
                                  filterPremiereEditR,
                                  filterRuntimeEditL,
                                  filterRuntimeEditR,
                                  filterGenreEdit,
                                  filterLanguageEdit);

    filterModel->setSourceModel(filmModel);

    masterView = new QTableView;
    masterView->setSortingEnabled(true);
    masterView->setModel(filterModel);

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(appLabel, 0, 0, 1, 2, Qt::AlignTop);
    layout->addWidget(masterView, 1, 0);
    layout->addWidget(detailsBox, 1, 1);
    layout->setRowStretch(1, 1);
    layout->addWidget(actions, 2, 0, 1, 2, Qt::AlignBottom);

    setStyleSheet("background-color: #FFFFFF;");
}

void MainPage::updateTitle(const QString& text)
{
    if(!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::title)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::title)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateIMDB(const QString& text)
{
    if(!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::imdb)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::imdb)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updatePremiere(const QString& text)
{
    if(!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::premiere)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::premiere)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateRuntime(const QString& text)
{
    if(!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::runtime)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::runtime)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateGenre(const QString& text)
{
    if(!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::genre)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::genre)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateLanguage(const QString& text)
{
    if(!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::language)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::language)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}


void MainPage::updateDetails(const QModelIndex &current, const QModelIndex &previous)
{
    if(!current.isValid())
        return;
    selectedCell = filterModel->mapToSource(current);
    titleEdit->setText(filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::title)].toString());
    imdbEdit->setText(filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::imdb)].toString());
    premiereEdit->setText(filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::premiere)].toString());
    runtimeEdit->setText(filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::runtime)].toString());
    genreEdit->setText(filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::genre)].toString());
    languageEdit->setText(filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::language)].toString());
}

void MainPage::addRows()
{
    filmModel->addRow();
    masterView->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
    masterView->verticalScrollBar()->setValue(1000);
}

void MainPage::deleteRows()
{
    if(!masterView->selectionModel()->hasSelection())
        return;
    filmModel->deleteRow(filterModel->mapToSource(masterView->selectionModel()->selectedIndexes().at(0)));
}

void MainPage::loadDataFunc()
{
  auto dir = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
  if (!dir.size())
      return;
  auto data = loadData(dir);
  filmModel->setData(data);
  for(int i = 0; i < static_cast<int>(FilmFields::COUNT); ++i)
      masterView->resizeColumnToContents(i);
  masterView->setColumnWidth(0, 200);
}

std::vector<Film> MainPage::loadData(const QString &dir)
{
    std::fstream file;
    std::vector<Film> result;
    try
    {
        file.open(dir.toStdString());
        std::string row, field;
        while(std::getline(file, row))
        {
            Film res;
            int i = 0;
            std::stringstream str(row);
            while(std::getline(str, field, ';'))
                res.data[i++] = QString(field.c_str());
            result.push_back(res);
        }
        file.close();
    }
    catch(...)
    {
        fileFailure();
    }
    return result;
}

void MainPage::saveDataFunc()
{
    auto dir = QFileDialog::getSaveFileName(this, "Save File As", QDir::currentPath ());
    if (!dir.size ())
      return;
    saveData (dir);
}

void MainPage::saveData(const QString &dir)
{
    std::ofstream file (dir.toStdString ());
    int total_columns = static_cast<int> (FilmFields::COUNT);
    for (auto &film : filmModel->m_data)
    {
        for (int i_column = 0; i_column < total_columns; ++i_column)
        {
            file << film.data[i_column].toString().toStdString();
            if (i_column < total_columns - 1)
                file << ";";
            else
                file << "\n";
        }
    }
}

void MainPage::fileFailure()
{
    QMessageBox alert;
    alert.setWindowTitle("Alert");
    alert.setText("Dear, Brazza.\r\nWe have some troubles with your file.\r\nPlease, choose the original dataset.");
    alert.setFont(QFont("Montserrat", 40));
    alert.setStyleSheet("QMessageBox{background-color: #24252A;}"
                        "QMessageBox QLabel {color: #FFFFFF; padding: 20; margin: 20}"
                        "QMessageBox QPushButton{font-family: Montserrat; font-size: 15px; padding: 10 50; background-color: #FFC107; color: #000000; border-radius: 5px;}"
                        "QMessageBox QPushButton:hover{background-color: #FFD218;}");
    alert.exec();
}

QVariant FilmModel::data (const QModelIndex &index, int role) const
{
    const Film &currentFilm = m_data[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return currentFilm.data[index.column()];
    return {};
}

const char *enum_to_string (FilmFields field)
{
    switch (field)
    {
        case FilmFields::title: return "Title";
        case FilmFields::imdb: return "IMDB Score";
        case FilmFields::premiere: return "Premiere";
        case FilmFields::runtime: return "Runtime";
        case FilmFields::genre: return "Genre";
        case FilmFields::language: return "Language";
        case FilmFields::COUNT: return "";
    }
    return {};
}

QVariant FilmModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return enum_to_string(FilmFields(section));
    return {};
}

bool FilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant lhv = left.data(Qt::EditRole);
    QVariant rhv = right.data(Qt::EditRole);
    if (left.column() == static_cast<int>(FilmFields::imdb))
        return lhv.toDouble() < rhv.toDouble();

    if (left.column() == static_cast<int>(FilmFields::premiere))
        return QDate::fromString(lhv.toString(), "dd.MM.yyyy") < QDate::fromString(rhv.toString(), "dd.MM.yyyy");

    if (left.column() == static_cast<int>(FilmFields::runtime))
        return lhv.toDouble() < rhv.toDouble();

    return lhv < rhv;
}

bool FilterModel::filterAcceptsRow (int sourceRow, const QModelIndex &sourceParent) const
{
    QString imdbmin = filterIMDBEditL->text();
    QString imdbmax = filterIMDBEditR->text();
    QDate prmin = filterPremiereEditL->date();
    QDate prmax = filterPremiereEditR->date();
    QString runtimemin = filterRuntimeEditL->text();
    QString runtimemax = filterRuntimeEditR->text();
    QString genreReq = filterGenreEdit->text();
    QString languageReq = filterLanguageEdit->text();

    QModelIndex imdb = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::imdb), sourceParent);
    QModelIndex premiere = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::premiere), sourceParent);
    QModelIndex runtime = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::runtime), sourceParent);
    QModelIndex genre = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::genre), sourceParent);
    QModelIndex language = sourceModel()->index(sourceRow, static_cast<int>(FilmFields::language), sourceParent);
    if(!imdbmin.isEmpty() && sourceModel()->data(imdb).toDouble() < imdbmin.toDouble())
        return false;
    if(!imdbmax.isEmpty() && sourceModel()->data(imdb).toDouble() > imdbmax.toDouble())
        return false;
    if(prmin.isValid() && QDate::fromString(sourceModel()->data(premiere).toString(), "dd.MM.yyyy") < prmin)
        return false;
    if(prmax.isValid() && QDate::fromString(sourceModel()->data(premiere).toString(), "dd.MM.yyyy") > prmax)
        return false;
    if(!runtimemin.isEmpty() && sourceModel()->data(runtime).toDouble() < runtimemin.toDouble())
        return false;
    if(!runtimemax.isEmpty() && sourceModel()->data(runtime).toDouble() > runtimemax.toDouble())
        return false;
    if(!genreReq.isEmpty() && sourceModel()->data(genre).toString() != genreReq)
        return false;
    if(!languageReq.isEmpty() && sourceModel()->data(language).toString() != languageReq)
        return false;
    return true;
}
