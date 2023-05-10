#include "nanduwidget.h"

NanDuWidget::NanDuWidget(QWidget *parent) : QWidget(parent)
{

    setupUi();

    connect(m_pMenuBar, SIGNAL(CurSelectPage(int)), this, SLOT(SelectButton(int)),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(showMax()), this, SLOT(click_on_Max()),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(showMin()), this, SLOT(click_on_Min()),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(closeWidget()), this, SLOT(click_on_closeall()),Qt::QueuedConnection);

    connect(m_ndMsgBox,SIGNAL(Clicked_btn_OK(int)),this,SLOT(click_on_msgok(int)),Qt::QueuedConnection);
    connect(m_ndMsgBox,SIGNAL(Clicked_btn_Cancel()),this,SLOT(click_on_msgcancel()),Qt::QueuedConnection);


}
void NanDuWidget::setupUi()
{
    w = new MainWindow();//new MainWindow(this);
    w->show();
    connect(w, SIGNAL(signal_send(int)), this, SLOT(led_change(int)),Qt::QueuedConnection);
//    setCentralWidget(widget);
    setAttribute(Qt::WA_StaticContents);
//    setFixedSize(1920,1080);
    setWindowTitle("子窗口");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/Config/Res/logo1"));

    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int currentScreenWid = screenRect.width();
    int currentScreenHei = screenRect.height();
    this->resize(currentScreenWid*3/4,currentScreenHei*4/5);

    m_ndMsgBox = new ndmassegebox(this);
    m_ndMsgBox->setGeometry((currentScreenWid-460)/2,(currentScreenHei-260)/2,460,260);
    m_ndMsgBox->setVisible(false);
    m_Darkwidge = new QWidget(this);
    m_Darkwidge->resize (currentScreenWid, currentScreenHei);
    m_Darkwidge->move (0,0);
    QPalette pal(m_Darkwidge->palette());
    m_Darkwidge->setStyleSheet("background-color:rgba(0, 0, 0, 60%);border-radius: 20px;");//透明如果主界面是圆角就要圆角
    m_Darkwidge->setAutoFillBackground(true);
    m_Darkwidge->setPalette(pal);
    m_Darkwidge->hide();

    QVBoxLayout *pMainLayOut = new QVBoxLayout(this);

    QVBoxLayout *pVSubLayOut = new QVBoxLayout(this);
    pVSubLayOut->setSpacing(0); //控件之间的边距
    m_pMenuBar = new MenuBarWid(this);

    m_StackedWidget = new QStackedWidget(this);
    mainwidget = new MainWidget(this);

    m_StackedWidget->addWidget(mainwidget);


   pVSubLayOut->addWidget(m_pMenuBar);
   pVSubLayOut->addWidget(m_StackedWidget);
   pVSubLayOut->setSpacing(0);

    QWidget* widbottom = new QWidget(this);
    widbottom->setStyleSheet("background-color:rgb(28,32,48)");

    QHBoxLayout *pLayOut_Bottom = new QHBoxLayout(widbottom);
    m_pTipAreaWid = new CTipAreaWid(this);
    m_pStateAreawid = new CStateWid(this);
    pLayOut_Bottom->addWidget(m_pTipAreaWid,5);
    pLayOut_Bottom->addWidget(m_pStateAreawid,5);
    pLayOut_Bottom->setSpacing(0);
    pLayOut_Bottom->setContentsMargins(0,0,0,0);

    pMainLayOut->addLayout(pVSubLayOut);
    pMainLayOut->addWidget(widbottom,0,Qt::AlignBottom);
    pMainLayOut->setContentsMargins(0,0,0,0);
    pMainLayOut->setSpacing(0); //控件之间的边距
    pMainLayOut->setMargin(0);
    widget->setLayout(pMainLayOut);

    /*
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
    m_pMenuBar = new MenuBarWid(this);
    vLayout[0]->addWidget(m_pMenuBar);
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
*/

}
NanDuWidget::~NanDuWidget()
{
    delete w;
}
void NanDuWidget::led_change(int led_num)
{
//qDebug()<<"nanduwidget:"<<led_num<<endl;
}

void NanDuWidget::SelectButton(int iCurSelectNum)
{

    int iturnNum = 0;
    if(iCurSelectNum < 4)
        iturnNum = iCurSelectNum;
    else
        iturnNum = 0;

//    m_StackedWidget->setCurrentIndex(iturnNum);


    if(iCurSelectNum == 4)
    {
        qDebug()<<"wd"<<endl;
        //弹框提示重启
        m_Darkwidge->show();
        qDebug()<<"wd"<<endl;
        m_ndMsgBox->setVisible(true);
        m_ndMsgBox->setType(0);
        m_ndMsgBox->setLabelText(tr("重启提醒"),tr("是否确认重启设备？"));
        qDebug()<<"wd"<<endl;
    }

    if(iCurSelectNum == 5)
    {
        //弹框提示关机
        m_Darkwidge->show();

        m_ndMsgBox->setVisible(true);
        m_ndMsgBox->setType(1);
        m_ndMsgBox->setLabelText(tr("关机提醒"),tr("是否确认关机？"));
    }
}
void NanDuWidget::click_on_closeall()
{
    delete w;
    close();
}
void NanDuWidget::click_on_Max()
{
    this->showFullScreen();
}
void NanDuWidget::click_on_Min()
{
    this->showMinimized();
}
void NanDuWidget::CloseSoft()
{
    delete w;
    close();
}
void NanDuWidget::click_on_msgok(int msgtype)
{
    m_Darkwidge->hide();

    if(msgtype == 0)
    {

        m_pMenuBar->setFirBtnChecked();
    }
    else if(msgtype == 1)
    {

        m_pMenuBar->setFirBtnChecked();
    }

    else
        ;

    //this->showFullScreen();
}
void NanDuWidget::click_on_msgcancel()
{
    m_Darkwidge->hide();
    m_pMenuBar->setFirBtnChecked();

    //this->showFullScreen();
}
