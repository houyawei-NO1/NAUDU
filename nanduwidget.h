#ifndef NANDUWIDGET_H
#define NANDUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QStackedWidget>
#include "mainwindow.h"
#include "menubarwid.h"
#include "ndmassegebox.h"
#include "ctipareawid.h"
#include "cstatewid.h"
#include "mainwidget.h"

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
    MenuBarWid* m_pMenuBar;
    ndmassegebox *m_ndMsgBox;
    QWidget *m_Darkwidge;
    CTipAreaWid *m_pTipAreaWid;
    CStateWid *m_pStateAreawid;
    QStackedWidget *m_StackedWidget;
    MainWidget *mainwidget;


signals:

public slots:
    void led_change(int);
    void SelectButton(int);
    void click_on_Max();
    void click_on_Min();
    void click_on_closeall();
    void CloseSoft();
    void click_on_msgok(int);
    void click_on_msgcancel();
};

#endif // NANDUWIDGET_H
