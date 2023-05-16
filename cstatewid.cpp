#include "cstatewid.h"

CStateWid::CStateWid(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground,true);
   this->setStyleSheet("background-color:rgb(43,48,70);");
   this->setMaximumHeight(40);
   this->setMinimumHeight(40);
   Init();
}

CStateWid::~CStateWid()
{

}

void CStateWid::Init()
{
    QHBoxLayout * pLay = new QHBoxLayout(this);

    QFont font;
    font.setPixelSize(13);

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);

    QString strColor="border-radius:8px;background-color:rgb(255,245,238)";
    m_vectext.append("开启设备");
    m_vectext.append("CAN初始化");
    m_vectext.append("CAN启动");
    m_vectext.append("数据接收");

    m_text_sortOne = new  QLabel(this);
    m_text_sortOne->setText(m_vectext.at(0));
    m_text_sortOne->setFont(font);
    m_color_sortOne = new  CDoubleButton(this);
    m_color_sortOne->setFixedSize(20,20);
    m_color_sortOne->setStyleSheet(strColor);
    m_color_sortOne->setFocusPolicy(Qt::NoFocus);

    m_text_sortTwo = new  QLabel(this);
    m_text_sortTwo->setText(m_vectext.at(1));
    m_text_sortTwo->setFont(font);
    m_color_sortTwo = new  CDoubleButton(this);
    m_color_sortTwo->setFixedSize(20,20);
    m_color_sortTwo->setStyleSheet(strColor);
    m_color_sortTwo->setFocusPolicy(Qt::NoFocus);

    m_text_sortThree = new  QLabel(this);
    m_text_sortThree->setText(m_vectext.at(2));
    m_text_sortThree->setFont(font);
    m_color_sortThree = new  CDoubleButton(this);
    m_color_sortThree->setFixedSize(20,20);
    m_color_sortThree->setStyleSheet(strColor);
    m_color_sortThree->setFocusPolicy(Qt::NoFocus);

    m_text_sortFour = new  QLabel(this);
    m_text_sortFour->setText(m_vectext.at(3));
    m_text_sortFour->setFont(font);
    m_color_sortFour = new  CDoubleButton(this);
    m_color_sortFour->setFixedSize(20,20);
    m_color_sortFour->setStyleSheet(strColor);
    m_color_sortFour->setFocusPolicy(Qt::NoFocus);


    m_text_sortOne->setPalette(pe);
    m_text_sortTwo->setPalette(pe);
    m_text_sortThree->setPalette(pe);
    m_text_sortFour->setPalette(pe);
    //m_text_weight->setPalette(pe);

    pLay->addStretch();
    pLay->addWidget(m_color_sortOne);
    pLay->addWidget(m_text_sortOne);
    pLay->addStretch();
    pLay->addWidget(m_color_sortTwo);
    pLay->addWidget(m_text_sortTwo);
    pLay->addStretch();
    pLay->addWidget(m_color_sortThree);
    pLay->addWidget(m_text_sortThree);
    pLay->addStretch();
    pLay->addWidget(m_color_sortFour);
    pLay->addWidget(m_text_sortFour);
    /*pLay->addStretch();
    pLay->addWidget(m_color_weight);
    pLay->addWidget(m_text_weight);*/
    pLay->setSpacing(20);
    pLay->setContentsMargins(20,0,20,0);

    connect(m_color_sortOne,SIGNAL(DoubleClick()),this,SLOT(click_on_BtnRfid()));
    connect(m_color_sortTwo,SIGNAL(DoubleClick()),this,SLOT(click_on_BtnThick()));
    connect(m_color_sortThree,SIGNAL(DoubleClick()),this,SLOT(click_on_BtnWaste()));
    connect(m_color_sortFour,SIGNAL(DoubleClick()),this,SLOT(click_on_BtnStamp()));
}



void CStateWid::click_on_BtnRfid()
{
    emit sigBtnClick(0,strService);
}

void CStateWid::click_on_BtnThick()
{
    emit sigBtnClick(1,strBhInfo);
}

void CStateWid::click_on_BtnWaste()
{
    emit sigBtnClick(2,strFzInfo);
}

void CStateWid::click_on_BtnStamp()
{
    emit sigBtnClick(3,strGaiZInfo);
}
void CStateWid::status_slot(bool iSta_Dev,bool iSta_CanInit,bool iSta_CanStart)
{
    if(iSta_Dev == true)
    {
        m_color_sortOne->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
    }
    else
    {
        m_color_sortOne->setStyleSheet("border-radius:8px;background-color:red");
    }

    if(iSta_CanInit == true)
    {
        m_color_sortTwo->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
    }
    else
    {
        m_color_sortTwo->setStyleSheet("border-radius:8px;background-color:red");
    }

    if(iSta_CanStart == true)
    {
        m_color_sortThree->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
    }
    else
    {
        m_color_sortThree->setStyleSheet("border-radius:8px;background-color:red");
    }
}
void CStateWid::DataRec_slot()
{

    m_color_sortFour->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
    QTimer::singleShot(1 * 1000,this,[=]{
                    m_color_sortFour->setStyleSheet("border-radius:8px;background-color:rgb(255,245,238)");
                });
}
