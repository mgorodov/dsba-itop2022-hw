#pragma once
#include "customdelegate.h"
#include "genresmodel.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <unordered_set>

class GenreSetter : public QWidget
{
    Q_OBJECT
public:
    GenreSetter(CustomDelegate* _customDelegate, GenresModel* _genresModel, QWidget* parent = nullptr);
    ~GenreSetter();

private:
    QLabel* genresLabel = nullptr;
    QPushButton* addBtn = nullptr;
    QPushButton* delBtn = nullptr;
    QTableView* genresList = nullptr;
    CustomDelegate* customDelegate = nullptr;
    GenresModel* genresModel = nullptr;
    GenresFilter* genresFilter = nullptr;
    void setupUI();

public slots:
    void addRow();
    void deleteRows();
};
