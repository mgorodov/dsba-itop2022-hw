#include "mainpage.h"

MainPage::MainPage(QWidget* parent)
    : QWidget(parent)
    , genresArr {
        "Action", "Adventure", "Aftershow", "Animation", "Anime", "Anthology",
        "Biopic", "Black humour", "Christmas", "Comedy", "Coming-of-age", "Crime",
        "Documentary", "Drama", "Family", "Fantasy", "Heist film", "Horror", "Historical-epic",
        "Mentalism special", "Musical", "One-man show",
        "Political thriller", "Psychological thriller",
        "Romance", "Romantic comedy", "Romantic drama",
        "Satire", "Science fiction", "Short", "Sports drama",
        "Spy thriller", "Superhero", "Supernatural drama",
        "Teen comedy horror", "Thriller",
        "Urban fantasy", "Variety show", "War",
        "Western", "Zombie"
    }
    , languagesArr { "Akan", "Arabic", "Bengali", "Dutch", "English", "Filipino", "French", "Georgian", "German", "Hindi", "Indonesian", "Italian", "Korean", "Mandarin", "Malay", "Marathi", "Norwegian", "Polish", "Portuguese", "Russian", "Spanish", "Swedish", "Thai", "Turkish", "Japanese" }
{
    setupUI();
    connect(addBtn, SIGNAL(clicked()), SLOT(addRows()));
    connect(delBtn, SIGNAL(clicked()), SLOT(deleteRows()));
    connect(uploadBtn, SIGNAL(clicked()), SLOT(loadDataFunc()));
    connect(saveBtn, SIGNAL(clicked()), SLOT(saveDataFunc()));
    connect(masterView->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(updateDetails(QModelIndex, QModelIndex)));

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
    connect(genreSetterBtn, SIGNAL(clicked()), SLOT(openGenreSetter()));
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

    QHBoxLayout* actLayout = new QHBoxLayout;
    actLayout->addWidget(addBtn);
    actLayout->addWidget(delBtn);
    actLayout->addWidget(uploadBtn);
    actLayout->addWidget(saveBtn);

    QGroupBox* actions = new QGroupBox;
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
    filterIMDBEditL->setValidator(new QDoubleValidator(0, 10, 1));
    filterIMDBEditR = new QLineEdit("");
    filterIMDBEditL->setValidator(new QDoubleValidator(0, 10, 1));
    filterPremiereEditL = new QDateEdit(QDate(2010, 1, 1));
    filterPremiereEditR = new QDateEdit(QDate(2022, 1, 1));
    filterRuntimeEditL = new QLineEdit("");
    filterRuntimeEditL->setValidator(new QIntValidator(1, 300));
    filterRuntimeEditR = new QLineEdit("");
    filterRuntimeEditL->setValidator(new QIntValidator(1, 300));
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
    imdbEdit->setValidator(new QDoubleValidator(0, 10, 1));
    premiereEdit = new QLineEdit("");
    premiereEdit->setValidator(new QRegExpValidator(QRegExp("(0[1-9]|[12][0-9]|3[01]).(0[1-9]|[1][0-2]).(19[0-9][0-9]|20[0-9][0-9])")));
    runtimeEdit = new QLineEdit("");
    runtimeEdit->setValidator(new QIntValidator(1, 300));
    genreEdit = new QLineEdit("");
    languageEdit = new QLineEdit("");
    genreSetterBtn = new QPushButton("Edit genres");
    genreSetterBtn->setFont(QFont("Montserrat", 25));
    genreSetterBtn->setStyleSheet("QPushButton{padding: 10 45; margin: 0 0; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                                  "QPushButton:hover{background-color: #1199BA;}");

    QGridLayout* details = new QGridLayout;
    details->setContentsMargins(0, 0, 0, 0);
    details->addWidget(filterLabel, 0, 0, 1, 4, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterIMDBFrom, 1, 0, Qt::AlignTop);
    details->addWidget(filterIMDBEditL, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterIMDBTo, 1, 2, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterIMDBEditR, 1, 3, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterPremiereFrom, 2, 0, Qt::AlignTop);
    details->addWidget(filterPremiereEditL, 2, 1, Qt::AlignTop);
    details->addWidget(filterPremiereTo, 2, 2, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterPremiereEditR, 2, 3, Qt::AlignTop);
    details->addWidget(filterRuntimeFrom, 3, 0, Qt::AlignTop);
    details->addWidget(filterRuntimeEditL, 3, 1, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterRuntimeTo, 3, 2, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterRuntimeEditR, 3, 3, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterGenreLabel, 4, 0, Qt::AlignTop);
    details->addWidget(filterGenreEdit, 4, 1, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(filterLanguageLabel, 5, 0, Qt::AlignTop);
    details->addWidget(filterLanguageEdit, 5, 1, Qt::AlignTop | Qt::AlignHCenter);
    details->addWidget(genreSetterBtn, 4, 3, 2, 1, Qt::AlignVCenter | Qt::AlignHCenter);
    details->addWidget(detailsLabel, 6, 0, 1, 4, Qt::AlignBottom | Qt::AlignHCenter);
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

    QGroupBox* detailsBox = new QGroupBox;
    detailsBox->setLayout(details);
    detailsBox->setStyleSheet("QGroupBox{padding: 10 10;}"
                              "QGroupBox QLabel{font-size: 30px;}"
                              "QGroupBox QLineEdit{font-size: 30px;}"
                              "QGroupBox QDateEdit{font-size: 30px;}");

    filterLabel->setStyleSheet("font-weight: 500; font-size 35px;");
    detailsLabel->setStyleSheet("font-weight: 500; font-size 35px;");

    genresModel = new GigaModel(genresArr, "Genres");
    languagesModel = new GigaModel(languagesArr, "Languages");
    customDelegate = new CustomDelegate(genresModel, languagesModel);
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
    masterView->setItemDelegate(customDelegate);

    QGridLayout* layout = new QGridLayout(this);
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
    if (!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::title)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::title)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateIMDB(const QString& text)
{
    if (!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::imdb)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::imdb)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updatePremiere(const QString& text)
{
    if (!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::premiere)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::premiere)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateRuntime(const QString& text)
{
    if (!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::runtime)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::runtime)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateGenre(const QString& text)
{
    if (!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::genre)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::genre)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateLanguage(const QString& text)
{
    if (!selectedCell.isValid() || filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::language)] == text)
        return;
    filmModel->beginResetModel();
    filmModel->m_data[selectedCell.row()].data[static_cast<int>(FilmFields::language)] = text;
    filmModel->endResetModel();
    emit filmModel->layoutChanged();
}

void MainPage::updateDetails(const QModelIndex& current, const QModelIndex& previous)
{
    if (!current.isValid())
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
    masterView->scrollToBottom();
    masterView->selectRow(filmModel->m_data.size() - 1);
    masterView->setFocus();
    filterIMDBEditL->setText("");
    filterIMDBEditR->setText("");
    filterPremiereEditL->setDate(QDate(2010, 1, 1));
    filterPremiereEditR->setDate(QDate(2022, 1, 1));
    filterRuntimeEditL->setText("");
    filterRuntimeEditR->setText("");
    filterGenreEdit->setText("");
    filterLanguageEdit->setText("");
}

void MainPage::deleteRows()
{
    if (!masterView->selectionModel()->hasSelection())
        return;
    std::unordered_set<size_t> selectedRows;
    for (const QModelIndex& ind : masterView->selectionModel()->selectedIndexes())
        selectedRows.insert(filterModel->mapToSource(ind).row());
    filmModel->deleteRows(selectedRows);
}

void MainPage::loadDataFunc()
{
    auto dir = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
    if (!dir.size())
        return;
    std::vector<Film> data = loadData(dir);
    filmModel->setData(data);
    std::set<QString> genresSet, languagesSet;
    for (const Film& g : data)
    {
        for (const QString& q : g.data[static_cast<size_t>(FilmFields::genre)].toString().split('/'))
            genresSet.insert(q);
        for (const QString& q : g.data[static_cast<size_t>(FilmFields::language)].toString().split('/'))
            languagesSet.insert(q);
    }
    if (genresModel)
        genresModel->setData(std::vector<QString>(genresSet.begin(), genresSet.end()));
    if (languagesModel)
        languagesModel->setData(std::vector<QString>(languagesSet.begin(), languagesSet.end()));
    for (int i = 0; i < static_cast<int>(FilmFields::COUNT); ++i)
        masterView->resizeColumnToContents(i);
    masterView->setColumnWidth(0, 200);
}

std::vector<Film> MainPage::loadData(const QString& dir)
{
    std::fstream file;
    std::vector<Film> result;
    try
    {
        file.open(dir.toStdString());
        std::string row, field;
        while (std::getline(file, row))
        {
            Film res;
            int i = 0;
            std::stringstream str(row);
            while (std::getline(str, field, ';'))
                res.data[i++] = QString(field.c_str());
            if (i < static_cast<int>(FilmFields::COUNT))
                throw "Bad file";
            result.push_back(res);
        }
        file.close();
    }
    catch (...)
    {
        fileFailure();
        return std::vector<Film>();
    }
    return result;
}

void MainPage::saveDataFunc()
{
    auto dir = QFileDialog::getSaveFileName(this, "Save File As", QDir::currentPath());
    if (!dir.size())
        return;
    saveData(dir);
}

void MainPage::saveData(const QString& dir)
{
    std::ofstream file(dir.toStdString());
    int total_columns = static_cast<int>(FilmFields::COUNT);
    for (auto& film : filmModel->m_data)
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

void MainPage::openGenreSetter()
{
    if (!gigaSetter)
        gigaSetter = new GigaSetter(customDelegate, genresModel, languagesModel);
    gigaSetter->show();
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

MainPage::~MainPage()
{
    delete appLabel;
    delete addBtn;
    delete delBtn;
    delete uploadBtn;
    delete saveBtn;

    delete filterLabel;
    delete filterIMDBFrom;
    delete filterIMDBTo;
    delete filterPremiereFrom;
    delete filterPremiereTo;
    delete filterRuntimeFrom;
    delete filterRuntimeTo;
    delete filterGenreLabel;
    delete filterLanguageLabel;
    delete genreSetterBtn;

    delete titleLabel;
    delete imdbLabel;
    delete premiereLabel;
    delete runtimeLabel;
    delete genreLabel;
    delete languageLabel;
    delete detailsLabel;

    delete filterIMDBEditL;
    delete filterIMDBEditR;
    delete filterPremiereEditL;
    delete filterPremiereEditR;
    delete filterRuntimeEditL;
    delete filterRuntimeEditR;
    delete filterGenreEdit;
    delete filterLanguageEdit;

    delete titleEdit;
    delete imdbEdit;
    delete premiereEdit;
    delete runtimeEdit;
    delete genreEdit;
    delete languageEdit;

    delete masterView;
    delete filmModel;
    delete filterModel;
    delete customDelegate;
    delete gigaSetter;
    delete genresModel;
    delete languagesModel;
}
