/*
    GigaSetter creates additional window, where user can manage lists of genres and languages
*/

#pragma once
#include "customdelegate.h"
#include "gigamodel.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <unordered_set>

class GigaSetter : public QWidget
{
    Q_OBJECT
public:
    GigaSetter(CustomDelegate* _customDelegate, GigaModel* _genresModel, GigaModel* _languagesModel, QWidget* parent = nullptr);
    ~GigaSetter();

private:
    QLabel* genresLabel = nullptr;
    QPushButton* addBtn = nullptr;
    QPushButton* delBtn = nullptr;
    QTableView* genresList = nullptr;
    QTableView* languagesList = nullptr;
    CustomDelegate* customDelegate = nullptr;
    GigaModel* genresModel = nullptr;
    GigaFilter* genresFilter = nullptr;
    GigaModel* languagesModel = nullptr;
    GigaFilter* languagesFilter = nullptr;
    void setupUI();

public slots:
    void addRow();
    void deleteRows();
    void genresSelected(const QModelIndex& current, const QModelIndex& previous);
    void languagesSelected(const QModelIndex& current, const QModelIndex& previous);
};
