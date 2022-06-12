#ifndef MAINMENU_H
#define MAINMENU_H

#include "mainpage.h"
#include "helppage.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
private:
    void setupUI();
    QLabel* menuLabel;
    QPushButton* startBtn;
    QPushButton* helpBtn;
    MainPage *mainPage = nullptr;
    HelpPage *helpPage = nullptr;
public slots:
    void startApp();
    void openHelp();

};
#endif // MAINMENU_H
