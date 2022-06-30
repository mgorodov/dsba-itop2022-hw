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
    HelpPage(QWidget* parent = nullptr);
    ~HelpPage() override;

private:
    QPushButton* aboutBtn = nullptr;
    LogoWidget* logoWidget = nullptr;
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
