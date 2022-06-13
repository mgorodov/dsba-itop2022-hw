#include "mainmenu.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    connect(startBtn, SIGNAL(clicked()), SLOT(startApp()));
    connect(helpBtn, SIGNAL(clicked()), SLOT(openHelp()));

}

void MainMenu::startApp()
{
    if(!mainPage) mainPage = new MainPage();
    mainPage->show();
}

void MainMenu::openHelp()
{
    if(!helpPage) helpPage = new HelpPage();
    helpPage->show();
}

void MainMenu::setupUI()
{
    resize(400, 600);
    startBtn = new QPushButton("START");
    helpBtn = new QPushButton("HELP");
    startBtn->setFont(QFont("Montserrat", 20));
    startBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                            "QPushButton:hover{background-color: #1199BA;}");
    helpBtn->setFont(QFont("Montserrat", 20));
    helpBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                           "QPushButton:hover{background-color: #1199BA;}");

    menuLabel = new QLabel("Main menu");
    menuLabel->setFont(QFont("Montserrat", 30));
    menuLabel->setStyleSheet("background-color: #24252A; color: #FFFFFF; padding: 15; border-bottom: 1px solid #FFFFFF");

    QVBoxLayout* btns = new QVBoxLayout;
    //btns->setAlignment();
    btns->addStretch();
    btns->addStretch();
    btns->addWidget(startBtn);
    btns->addStretch();
    btns->addWidget(helpBtn);
    btns->addStretch();
    btns->addStretch();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(menuLabel);
    layout->addLayout(btns);
    setStyleSheet("background-color: #24252A;");
}

MainMenu::~MainMenu()
{
}

