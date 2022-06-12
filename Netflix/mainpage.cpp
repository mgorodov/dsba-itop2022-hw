#include "mainpage.h"
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <iostream>

MainPage::MainPage(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
}

void MainPage::setupUI()
{
    resize(1366, 768);

    QGridLayout *layout = new QGridLayout(this);
    QGroupBox *master;
    QGroupBox *details;
    setStyleSheet("background-color: #24252A;");
}

void MainPage::loadDataTrigger()
{
  auto dir = QFileDialog::getOpenFileName (this, "Open File", QDir::currentPath ());
  if (!dir.size ())
    return;
  auto data = loadData(dir);
  //car_model->set_data (data);
}

std::vector<Film> MainPage::loadData(const QString &dir)
{
    std::fstream file;
    std::vector<Film> result;
    file.open(dir.toStdString ());
    std::string row, field;
    while(std::getline(file, row))
    {
        Film res;
        int i = 0;
        std::stringstream str(row);
        while(std::getline(str, field, ','))
        {
            res.data[i] = QString(field.c_str());
            ++i;
        }
        result.push_back(res);
    }
    file.close();
    return result;
}
