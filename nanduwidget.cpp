#include "nanduwidget.h"

NanDuWidget::NanDuWidget(QWidget *parent) : QWidget(parent)
{

    setupUi();
}
void NanDuWidget::setupUi()
{
    w = new MainWindow();//new MainWindow(this);
    w->show();
    connect(w, SIGNAL(signal_send(int)), this, SLOT(led_change(int)),Qt::QueuedConnection);
//    setCentralWidget(widget);
    setAttribute(Qt::WA_StaticContents);
    setFixedSize(400,500);
    setWindowTitle("子窗口");
    gLayout = new QGridLayout(widget);
//第一行
    vLayout[0] = new QVBoxLayout();
    pStatus[0] = new QLabel();
    tName[0] = new QLabel();
    pStatus[0]->setText("状态显示图片");
    tName[0] = new QLabel();
    tName[0]->setText("座椅开关");
    vLayout[0]->addWidget(pStatus[0]);
    vLayout[0]->addWidget(tName[0]);
    gLayout->addLayout(vLayout[0],0,0);

    vLayout[1] = new QVBoxLayout();
    pStatus[1] = new QLabel();
    tName[1] = new QLabel();
    pStatus[1]->setText("状态显示图片");
    tName[1] = new QLabel();
    tName[1]->setText("离合器踏板底部开关");
    vLayout[1]->addWidget(pStatus[1]);
    vLayout[1]->addWidget(tName[1]);
    gLayout->addLayout(vLayout[1],0,1);

    vLayout[2] = new QVBoxLayout();
    pStatus[2] = new QLabel();
    tName[2] = new QLabel();
    pStatus[2]->setText("状态显示图片");
    tName[2] = new QLabel();
    tName[2]->setText("非驻车制动信号");
    vLayout[2]->addWidget(pStatus[2]);
    vLayout[2]->addWidget(tName[2]);
    gLayout->addLayout(vLayout[2],0,2);

    vLayout[3] = new QVBoxLayout();
    pStatus[3] = new QLabel();
    tName[3] = new QLabel();
    pStatus[3]->setText("状态显示图片");
    tName[3] = new QLabel();
    tName[3]->setText("空挡开关");
    vLayout[3]->addWidget(pStatus[3]);
    vLayout[3]->addWidget(tName[3]);
    gLayout->addLayout(vLayout[3],0,3);

//第二行
    vLayout[4] = new QVBoxLayout();
    pStatus[4] = new QLabel();
    tName[4] = new QLabel();
    pStatus[4]->setText("状态显示图片");
    tName[4] = new QLabel();
    tName[4]->setText("双边制动信号");
    vLayout[4]->addStretch();
    vLayout[4]->addWidget(pStatus[4]);
    vLayout[4]->addWidget(tName[4]);
    gLayout->addLayout(vLayout[4],2,0);

//第三行




    widget->setLayout(gLayout);


}
NanDuWidget::~NanDuWidget()
{

}
void NanDuWidget::led_change(int led_num)
{
//qDebug()<<"nanduwidget:"<<led_num<<endl;
}
