#include "genresetter.h"

GenreSetter::GenreSetter(CustomDelegate* _customDelegate, GenresModel* _genresModel, QWidget* parent)
    : QWidget { parent }
    , customDelegate(_customDelegate)
    , genresModel(_genresModel)
{
    setupUI();
    connect(addBtn, SIGNAL(clicked()), SLOT(addRow()));
    connect(delBtn, SIGNAL(clicked()), SLOT(deleteRows()));
}

void GenreSetter::setupUI()
{
    resize(500, 800);

    genresLabel = new QLabel("Edit genres list");
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

    genresFilter = new GenresFilter;
    genresFilter->setSourceModel(genresModel);

    genresList = new QTableView;
    genresList->setModel(genresFilter);
    genresList->setSortingEnabled(true);
    genresList->sortByColumn(0, Qt::AscendingOrder);
    genresList->setColumnWidth(0, 300);

    QVBoxLayout* btns = new QVBoxLayout;
    btns->addWidget(addBtn);
    btns->addWidget(delBtn);

    QGridLayout* layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(genresLabel, 0, 0, 1, 2, Qt::AlignTop);
    layout->addWidget(genresList, 1, 0);
    layout->addLayout(btns, 1, 1, Qt::AlignVCenter);
    layout->setRowStretch(1, 1);

    setStyleSheet("background-color: #FFFFFF;");
}

void GenreSetter::addRow()
{
    genresModel->addRow();
    genresList->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
    genresList->scrollToBottom();
    genresList->selectRow(genresModel->m_data.size() - 1);
}

void GenreSetter::deleteRows()
{
    if (!genresList->selectionModel()->hasSelection())
        return;
    std::unordered_set<size_t> selectedRows;
    for (const QModelIndex& ind : genresList->selectionModel()->selectedIndexes())
        selectedRows.insert(ind.row());
    genresModel->deleteRows(selectedRows);
}

GenreSetter::~GenreSetter()
{
    delete genresLabel;
    delete addBtn;
    delete delBtn;
    delete genresList;
    delete genresFilter;
}
