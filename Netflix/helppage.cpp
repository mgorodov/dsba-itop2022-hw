#include "helppage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>

HelpPage::HelpPage(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
    connect(aboutBtn, SIGNAL(clicked()), SLOT(about()));
}

void HelpPage::setupUI()
{
    resize(400, 600);

    logoWidget = new LogoWidget();

    aboutBtn = new QPushButton("ABOUT");
    aboutBtn->setFont(QFont("Montserrat", 20));
    aboutBtn->setStyleSheet("QPushButton{padding: 20; margin: 10 30; background-color: #0088A9; color: #FFFFFF; border-radius: 15px;}"
                            "QPushButton:hover{background-color: #1199BA;}");

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(logoWidget);
    layout->addWidget(aboutBtn);

    setStyleSheet("background-color: #24252A;");
}

void HelpPage::about()
{
    QMessageBox alert;
    alert.setWindowTitle("About");
    alert.setText("Student ID: 125");
    alert.setFont(QFont("Montserrat", 40));
    alert.setStyleSheet("QMessageBox{background-color: #24252A;}"
                        "QMessageBox QLabel {color: #FFFFFF; padding: 20; margin: 20}"
                        "QMessageBox QPushButton{font-family: Montserrat; font-size: 15px; padding: 10 50; background-color: #0088A9; color: #FFFFFF; border-radius: 5px;}"
                        "QMessageBox QPushButton:hover{background-color: #1199BA;}");
    alert.exec();
}

LogoWidget::LogoWidget(QWidget *parent)
{
}

void LogoWidget::paintEvent (QPaintEvent *event)
{
  int cx = width() / 2, cy = height() / 2;
  double st = std::min(cx*6/4, cy);
  QPainter painter (this);
  painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
  painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
  // Pen    lines,
  // Brush  fill
  painter.setPen (QPen(Qt::white, 4));

  painter.drawLine(cx-st/2, cy-st/3, cx-st/2+0.85*st, cy-st/3-0.3*st);
  painter.drawLine(cx-st/2, cy-st/3, cx-st/2-0.2*0.3*st, cy-st/3-0.2*0.85*st);
  painter.drawLine(cx-st/2+0.85*st, cy-st/3-0.3*st, cx-st/2+0.85*st-0.2*0.3*st, cy-st/3-0.3*st-0.2*0.85*st);
  painter.drawLine(cx-st/2-0.2*0.3*st, cy-st/3-0.2*0.85*st, cx-st/2+0.85*st-0.2*0.3*st, cy-st/3-0.3*st-0.2*0.85*st);

  painter.drawLine(cx-st/2+0.2*0.85*st, cy-st/3-0.2*0.3*st, cx-st/2+0.98*(-0.2*0.3*st+0.38*0.85*st), cy-st/3+0.98*(-0.2*0.85*st-0.38*0.3*st));
  painter.drawLine(cx-st/2+0.45*0.85*st, cy-st/3-0.45*0.3*st, cx-st/2+0.98*(-0.2*0.3*st+0.63*0.85*st), cy-st/3+0.98*(-0.2*0.85*st-0.63*0.3*st));
  painter.drawLine(cx-st/2+0.7*0.85*st, cy-st/3-0.7*0.3*st, cx-st/2+0.98*(-0.2*0.3*st+0.88*0.85*st), cy-st/3+0.98*(-0.2*0.85*st-0.88*0.3*st));


  painter.drawLine(cx-st/2, cy-st/3, cx+st/2, cy-st/3);
  painter.drawLine(cx-st/2, cy-st/3, cx-st/2, cy+st/3);
  painter.drawLine(cx-st/2, cy+st/3, cx+st/2, cy+st/3);
  painter.drawLine(cx+st/2, cy-st/3, cx+st/2, cy+st/3);

  painter.drawLine(cx-st/2, cy-st/9, cx+st/2, cy-st/9);
  painter.drawLine(cx-st/5, cy-st/9, cx-st/5-2*st/9, cy-st/3);
  painter.drawLine(cx+st/10, cy-st/9, cx+st/10-2*st/9, cy-st/3);
  painter.drawLine(cx+4*st/10, cy-st/9, cx+4*st/10-2*st/9, cy-st/3);


}
