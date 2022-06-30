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
    ~MainMenu() override;

private:
    void setupUI();
    QLabel* menuLabel = nullptr;
    QPushButton* startBtn = nullptr;
    QPushButton* helpBtn = nullptr;
    MainPage* mainPage = nullptr;
    HelpPage* helpPage = nullptr;

public slots:
    void startApp();
    void openHelp();
};
