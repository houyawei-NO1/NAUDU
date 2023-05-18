#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:black;");//rgb(28,32,48)
    this->setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
//    currentScreenWid = (screenRect.width()*3/4);
//    currentScreenHei = (screenRect.height()*4/5 - 100);
    currentScreenWid = (screenRect.width());
    currentScreenHei = (screenRect.height() - 100);
    this->setFixedSize(currentScreenWid,currentScreenHei);

    gridlayout = new QGridLayout(this);
    gridlayout->setMargin(0);
    Init();
    gridlayout->setMargin(10);
//    setLayout(gridlayout);

}
MainWidget::Init()
{

//    QWidget* top = new QWidget(this);
//    gridlayout->addWidget(top,0,0,1,14);

    ledwidget[0] = new LedWidget(this);
    ledwidget[0]->show();
    ledwidget[0]->Init("座椅开关");
    gridlayout->addWidget(ledwidget[0],0,0,2,2);
    ledwidget[1] = new LedWidget(this);
    ledwidget[1]->show();
    ledwidget[1]->Init("离合器");
    gridlayout->addWidget(ledwidget[1],0,2,2,2);
    ledwidget[2] = new LedWidget(this);
    ledwidget[2]->show();
    ledwidget[2]->Init("驻车制动(大拖)");
    gridlayout->addWidget(ledwidget[2],0,4,2,2);

    ledwidget[3] = new LedWidget(this);
    ledwidget[3]->show();
    ledwidget[3]->Init("空挡");
    gridlayout->addWidget(ledwidget[3],2,0,2,2);
    ledwidget[4] = new LedWidget(this);
    ledwidget[4]->show();
    ledwidget[4]->Init("双边制动");
    gridlayout->addWidget(ledwidget[4],2,2,2,2);
    ledwidget[5] = new LedWidget(this);
    ledwidget[5]->show();
    ledwidget[5]->Init("PTO使能");
    gridlayout->addWidget(ledwidget[5],2,4,2,2);

    ledwidget[6] = new LedWidget(this);
    ledwidget[6]->show();
    ledwidget[6]->Init("PTO外部");
    gridlayout->addWidget(ledwidget[6],4,0,2,2);
    ledwidget[7] = new LedWidget(this);
    ledwidget[7]->show();
    ledwidget[7]->Init("提升器位置");
    gridlayout->addWidget(ledwidget[7],4,2,2,2);
    ledwidget[8] = new LedWidget(this);
    ledwidget[8]->show();
    ledwidget[8]->Init("提升器低位");
    gridlayout->addWidget(ledwidget[8],4,4,2,2);

    ledwidget[9] = new LedWidget(this);
    ledwidget[9]->show();
    ledwidget[9]->Init("驻车制动(中小拖)");
    gridlayout->addWidget(ledwidget[9],6,0,2,2);
    ledwidget[10] = new LedWidget(this);
    ledwidget[10]->show();
    ledwidget[10]->Init("四驱使能");
    gridlayout->addWidget(ledwidget[10],6,2,2,2);
    ledwidget[11] = new LedWidget(this);
    ledwidget[11]->show();
    ledwidget[11]->Init("提升器位置角度");
    gridlayout->addWidget(ledwidget[11],6,4,2,2);

//    QWidget* buttom = new QWidget(this);
//    gridlayout->addWidget(buttom,7,0,3,8);


    chartviewwid[0] = new ChartViewWid(this);
    chartviewwid[0]->Init("启动电磁阀");
    chartviewwid[1] = new ChartViewWid(this);
    chartviewwid[1]->Init("四驱电磁阀");
    chartviewwid[2] = new ChartViewWid(this);
    chartviewwid[2]->Init("蜂鸣器电磁阀");
    chartviewwid[3] = new ChartViewWid(this);
    chartviewwid[3]->Init("PTO电磁阀");
    gridlayout->addWidget(chartviewwid[0],0,6,4,4);
    gridlayout->addWidget(chartviewwid[1],0,10,4,4);
    gridlayout->addWidget(chartviewwid[2],4,6,4,4);
    gridlayout->addWidget(chartviewwid[3],4,10,4,4);
    electric_change(0,0,0,0);
    m_totlenum = 0;


}
void MainWidget::led_change(int id, bool iflag)
{
//    qDebug()<<"id:"<<id<<"  iflag:"<<iflag<<endl;
    ledwidget[id]->LedChange(iflag);
    Cal_TotleNum();
}

void MainWidget::electric_change(int numa,int numb,int numc,int numd)
{

    chartviewwid[0]->ElectricChange(numa);
    chartviewwid[1]->ElectricChange(numb);
    chartviewwid[2]->ElectricChange(numc);
    chartviewwid[3]->ElectricChange(numd);
}
void MainWidget::ReInit()
{
    //新控制器上电前重新初始化准备
    //led灯状态重置
    for(int i= 0;i<12;++i)
    {
         ledwidget[i]->ReInit();
    }
    for(int j =0;j<4;j++)
    {
        chartviewwid[j]->ReInit();
    }
    m_totlenum = 0;
}
void MainWidget::Cal_TotleNum()
{
    m_totlenum = 0;
    for(int i= 0;i<12;++i)
    {
         m_totlenum = ledwidget[i]->m_result + m_totlenum;
    }
    send_TotleNum(m_totlenum);
//    qDebug()<<m_totlenum<<endl;
}



