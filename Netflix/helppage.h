/***************************************************************************************************

  Help window with logo and about button

***************************************************************************************************/

#pragma once

#include <QPushButton>
#include <QWidget>

class LogoWidget;
class HelpPage : public QWidget
{
    Q_OBJECT
public:
    explicit HelpPage(QWidget* parent = nullptr);

private:
    QPushButton* aboutBtn;
    LogoWidget* logoWidget;
    void setupUI();

public slots:
    void about();
};

class LogoWidget : public QWidget
{
    Q_OBJECT

public:
    LogoWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};
