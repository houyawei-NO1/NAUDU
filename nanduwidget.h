#ifndef NANDUWIDGET_H
#define NANDUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include "mainwindow.h"
#include <QDebug>

class NanDuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NanDuWidget(QWidget *parent = nullptr);
    ~NanDuWidget();
    void setupUi();

private:
    QWidget *widget=new QWidget(this);
    QGridLayout *gLayout;
    QVBoxLayout *vLayout[12];
    QLabel *pStatus[12];
    QLabel *tName[12];
    MainWindow *w;


signals:

public slots:
    void led_change(int);
};

#endif // NANDUWIDGET_H
