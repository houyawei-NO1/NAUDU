#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "ledwidget.h"
#include "chartviewwid.h"
#include "resultdialog.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    int currentScreenWid;//整个主部件区域大小
    int currentScreenHei;//整个主部件区域大小
    Init();



signals:
    void send_TotleNum(int);
    void send_BuhegeXiangmu(QString);

public slots:
    void led_change(int,bool);
    void electric_change(int,int,int,int);
    void ReInit();
    void Cal_TotleNum();

private:
    LedWidget *ledwidget[12];
    ChartViewWid *chartviewwid[4];
    ResultDialog *resultDialog;
    QHBoxLayout *mainlayout;
    QGridLayout *gridlayout_left;
    QGridLayout *gridlayout_right;
    QLabel *a,*b,*c,*d;
    int m_totlenum;
    QString m_buhege;
};

#endif // MAINWIDGET_H
