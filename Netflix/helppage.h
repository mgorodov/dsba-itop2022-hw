#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QWidget>
#include <QPushButton>

class LogoWidget;
class HelpPage : public QWidget
{
    Q_OBJECT
public:
    explicit HelpPage(QWidget *parent = nullptr);
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
  LogoWidget(QWidget *parent = nullptr);
protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif // HELPPAGE_H
