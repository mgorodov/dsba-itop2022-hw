/***************************************************************************************************

  Main menu with two buttons start and help

***************************************************************************************************/

#pragma once

#include "helppage.h"
#include "mainpage.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget* parent = nullptr);
    ~MainMenu();

private:
    void setupUI();
    QLabel* menuLabel;
    QPushButton* startBtn;
    QPushButton* helpBtn;
    MainPage* mainPage = nullptr;
    HelpPage* helpPage = nullptr;

public slots:
    void startApp();
    void openHelp();
};
