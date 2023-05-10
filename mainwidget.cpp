#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:black;");//rgb(28,32,48)
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    currentScreenWid = (screenRect.width()*3/4);
    currentScreenHei = (screenRect.height()*4/5 - 100);
    this->setFixedSize(currentScreenWid,currentScreenHei);
}
