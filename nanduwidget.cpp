#include "nanduwidget.h"

NanDuWidget::NanDuWidget(QWidget *parent) : QWidget(parent)
{

    setupUi();

    //功能状态
    connect(w, SIGNAL(signal_send(int,bool)), mainwidget, SLOT(led_change(int,bool)),Qt::QueuedConnection);
    connect(w, SIGNAL(electric_send(int,int,int,int)), mainwidget, SLOT(electric_change(int,int,int,int)),Qt::QueuedConnection);
    //菜单栏
    connect(m_pMenuBar,SIGNAL(CurSelectPage(int)), this, SLOT(SelectButton(int)),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(showMax()), this, SLOT(click_on_Max()),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(showMin()), this, SLOT(click_on_Min()),Qt::QueuedConnection);
    connect(m_pMenuBar, SIGNAL(closeWidget()), this, SLOT(click_on_closeall()),Qt::QueuedConnection);
    //弹窗
    connect(m_ndMsgBox,SIGNAL(Clicked_btn_OK(int)),this,SLOT(click_on_msgok(int)),Qt::QueuedConnection);
    connect(m_ndMsgBox,SIGNAL(Clicked_btn_Cancel()),this,SLOT(click_on_msgcancel()),Qt::QueuedConnection);


    //自动连接
    w->ConnectDev();

}
void NanDuWidget::setupUi()
{
    w = new MainWindow();//new MainWindow(this);
//    w->show();
//    connect(w, SIGNAL(signal_send(int)), this, SLOT(led_change(int)),Qt::QueuedConnection);
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
//    this->resize(currentScreenWid*3/4,currentScreenHei*4/5);
    this->resize(currentScreenWid,currentScreenHei);

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

    QVBoxLayout *pVSubLayOut = new QVBoxLayout();
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
//    widget->setLayout(pMainLayOut);

}
NanDuWidget::~NanDuWidget()
{
    delete w;
}

void NanDuWidget::SelectButton(int iCurSelectNum)
{

    int iturnNum = 0;
    if(iCurSelectNum < 4)
        iturnNum = iCurSelectNum;
    else
        iturnNum = 0;

//    m_StackedWidget->setCurrentIndex(iturnNum);
    if(iCurSelectNum==1)
    {
        qDebug()<<"w->ResetDev()"<<endl;
        w->ResetDev();
    }

    if(iCurSelectNum==2)
    {

        w->show();
    }

    if(iCurSelectNum == 4)
    {

        //弹框提示重启
        m_Darkwidge->show();
        m_ndMsgBox->setVisible(true);
        m_ndMsgBox->setType(0);
        m_ndMsgBox->setLabelText(tr("重启提醒"),tr("是否确认重启设备？"));
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
