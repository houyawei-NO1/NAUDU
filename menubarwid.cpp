#include "menubarwid.h"

MenuBarWid::MenuBarWid(QWidget *parent) : QWidget(parent)
{
    setupUi();

}
void MenuBarWid::setupUi()
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    setWindowFlags(Qt::FramelessWindowHint);
   this->setStyleSheet("background-color:rgb(43,48,70)");

//   setMaximumHeight(60);
//   setMinimumHeight(60);

   m_ItotleNum = 0;

   m_bMode = true;
   Init();
}

MenuBarWid::~MenuBarWid()
{

}

void MenuBarWid::Init()
{
    QHBoxLayout *main_layout = new QHBoxLayout(this);

    QHBoxLayout *title_layout = new QHBoxLayout();
    m_pVersion_title = new QLabel(this);
    QLabel *logo_label = new QLabel(this);
    QPixmap pixmap(":/Config/Res/logo.png");
    logo_label->setPixmap(pixmap);
    logo_label->setCursor(Qt::PointingHandCursor);

    m_pVersion_title->setMaximumHeight(20);
    logo_label->setMaximumWidth(120);
    logo_label->setAlignment(Qt::AlignCenter);
    m_pVersion_title->setAlignment(Qt::AlignCenter);

    title_layout->addWidget(logo_label);
    title_layout->addWidget(m_pVersion_title);
    title_layout->setSpacing(15);


    QHBoxLayout *button_layout = new QHBoxLayout();
    pushButtonGroup = new QButtonGroup(this);
    pushButtonGroup->setExclusive(true);
    connect(pushButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slot_btnGroupClicked(int)));
    for(int i=0; i<6; i++)
    {
        QPushButton *tool_button = new QPushButton(this);//font-family: Microsoft YaHei;
        tool_button->setFixedSize(80,60);
        tool_button->setCheckable(true);
        tool_button->autoExclusive();
        tool_button->setFocusPolicy(Qt::NoFocus);
        tool_button->setStyleSheet("QPushButton{color:white;font:17px;border-radius:0px}"
                                   "QPushButton:checked{color:#1a67c0;background:#273d64;font:17px;border-bottom:1px solid #1673db}");
        pushButtonGroup->addButton(tool_button,i);
        button_layout->addWidget(tool_button, 0, Qt::AlignHCenter);

        if(i == 0)
            tool_button->setChecked(true);
    }
    button_layout->addStretch();
    button_layout->setSpacing(30);
    button_layout->setContentsMargins(50, 0, 0, 0);


    QHBoxLayout *count_layout = new QHBoxLayout();
    QLabel* lb_TotleNum = new QLabel(this);
    lb_TotleNum->setStyleSheet("color:#66ff00;font:20px");
    lb_TotleNum->setText("总数:");
    m_lbTotleNum = new QLabel(this);
    m_lbTotleNum->setStyleSheet("color:#66ff00;font:20px");
    m_lbTotleNum->setText("0 ");
    count_layout->addWidget(lb_TotleNum);
    count_layout->addWidget(m_lbTotleNum);
    count_layout->setSpacing(5);


    m_pMin_button = new PushButton();
    m_pMax_button = new PushButton();
    m_pClose_button = new PushButton();
    //设置图片
    m_pMin_button->loadPixmap(":/image/min_button");
    m_pMax_button->loadPixmap(":/image/max_button");
    m_pClose_button->loadPixmap(":/image/close_button");

    connect(m_pMin_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
    connect(m_pMax_button, SIGNAL(clicked()), this, SIGNAL(showMax()));
    connect(m_pClose_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));

    main_layout->addLayout(title_layout);
    main_layout->addLayout(button_layout);
    main_layout->addStretch();
    main_layout->addLayout(count_layout);
    main_layout->addStretch();

    main_layout->addWidget(m_pMin_button,0,Qt::AlignCenter);
    main_layout->addWidget(m_pMax_button,0,Qt::AlignCenter);
    main_layout->addWidget(m_pClose_button,0,Qt::AlignCenter);
    main_layout->setContentsMargins(10,0,10,0);

    this->translateLanguage();
}

void MenuBarWid::translateLanguage()
{
    m_pVersion_title->setText("南都汽车安全控制器检测");
    m_pVersion_title->setStyleSheet("color:white");

    pushButtonGroup->button(0)->setText("主界面");
    pushButtonGroup->button(1)->setText("复位");
    pushButtonGroup->button(2)->setText("设置");
    pushButtonGroup->button(3)->setText("数据接收");
    pushButtonGroup->button(4)->setText("重启");
    pushButtonGroup->button(5)->setText("关机");

}


void MenuBarWid::slot_btnGroupClicked(int btnNum)
{
    /*if(btnNum == 2)
        emit CurSelectPage(0);
    else if(btnNum > 2)
        emit CurSelectPage(btnNum - 1);
    else
        emit CurSelectPage(btnNum);*/


    emit CurSelectPage(btnNum);
}

void MenuBarWid::setFirBtnChecked()
{
    pushButtonGroup->button(0)->setChecked(true);
}


void MenuBarWid::slotSetTotleNum()
{
    m_ItotleNum++;
    m_lbTotleNum->setText(QString::number(m_ItotleNum));
}
