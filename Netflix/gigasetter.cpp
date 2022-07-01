#include "gigasetter.h"

GigaSetter::GigaSetter(CustomDelegate* _customDelegate, GigaModel* _genresModel, GigaModel* _languagesModel, QWidget* parent)
    : QWidget { parent }
    , customDelegate(_customDelegate)
    , genresModel(_genresModel)
    , languagesModel(_languagesModel)
{
    setupUI();
    connect(addBtn, SIGNAL(clicked()), SLOT(addRow()));
    connect(delBtn, SIGNAL(clicked()), SLOT(deleteRows()));
    connect(genresList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(genresSelected(QModelIndex, QModelIndex)));
    connect(languagesList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(languagesSelected(QModelIndex, QModelIndex)));
}

void GigaSetter::setupUI()
{
    resize(800, 800);

    genresLabel = new QLabel("Edit genres and languages list");
    genresLabel->setFont(QFont("Montserrat", 30));
    genresLabel->setStyleSheet("background-color: #24252A; color: #FFFFFF; padding: 15; margin: 0; border-bottom: 1px solid #FFFFFF");

    addBtn = new QPushButton("ADD");
    delBtn = new QPushButton("DEL");
    addBtn->setFont(QFont("Montserrat", 25));
    addBtn->setStyleSheet("QPushButton{padding: 20 40; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                          "QPushButton:hover{background-color: #1199BA;}");
    delBtn->setFont(QFont("Montserrat", 25));
    delBtn->setStyleSheet("QPushButton{padding: 20 40; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                          "QPushButton:hover{background-color: #1199BA;}");

    genresFilter = new GigaFilter;
    genresFilter->setSourceModel(genresModel);

    languagesFilter = new GigaFilter;
    languagesFilter->setSourceModel(languagesModel);

    genresList = new QTableView;
    genresList->setModel(genresFilter);
    genresList->setSortingEnabled(true);
    genresList->sortByColumn(0, Qt::AscendingOrder);
    genresList->setColumnWidth(0, 300);

    languagesList = new QTableView;
    languagesList->setModel(languagesFilter);
    languagesList->setSortingEnabled(true);
    languagesList->sortByColumn(0, Qt::AscendingOrder);
    languagesList->setColumnWidth(0, 300);

    QVBoxLayout* btns = new QVBoxLayout;
    btns->addWidget(addBtn);
    btns->addWidget(delBtn);

    QGridLayout* layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(genresLabel, 0, 0, 1, 3, Qt::AlignTop);
    layout->addWidget(genresList, 1, 0);
    layout->addWidget(languagesList, 1, 1);
    layout->addLayout(btns, 1, 2, Qt::AlignVCenter);
    layout->setRowStretch(1, 1);

    setStyleSheet("background-color: #FFFFFF;");
}

void GigaSetter::addRow()
{
    if (languagesList->selectionModel()->hasSelection())
    {
        languagesModel->addRow();
        languagesList->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
        languagesList->scrollToBottom();
        languagesList->selectRow(languagesModel->m_data.size() - 1);
        languagesList->setFocus();
    }
    if (genresList->selectionModel()->hasSelection())
    {
        genresModel->addRow();
        genresList->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
        genresList->scrollToBottom();
        genresList->selectRow(genresModel->m_data.size() - 1);
        genresList->setFocus();
    }
}

void GigaSetter::deleteRows()
{
    if (languagesList->selectionModel()->hasSelection())
    {
        std::unordered_set<size_t> selectedRows;
        for (const QModelIndex& ind : languagesList->selectionModel()->selectedIndexes())
            selectedRows.insert(ind.row());
        languagesModel->deleteRows(selectedRows);
    }
    if (genresList->selectionModel()->hasSelection())
    {
        std::unordered_set<size_t> selectedRows;
        for (const QModelIndex& ind : genresList->selectionModel()->selectedIndexes())
            selectedRows.insert(ind.row());
        genresModel->deleteRows(selectedRows);
    }
}

void GigaSetter::genresSelected(const QModelIndex& current, const QModelIndex& previous)
{
    if (!current.isValid())
        return;
    languagesList->clearSelection();
}

void GigaSetter::languagesSelected(const QModelIndex& current, const QModelIndex& previous)
{
    if (!current.isValid())
        return;
    genresList->clearSelection();
}

GigaSetter::~GigaSetter()
{
    delete genresLabel;
    delete addBtn;
    delete delBtn;
    delete genresList;
    delete languagesList;
    delete genresFilter;
    delete languagesFilter;
}
