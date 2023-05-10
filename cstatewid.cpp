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

    QString strColor="border-radius:8px;background-color:rgb(67,207,124)";
    m_vectext.append("服务器");
    m_vectext.append("相机");
    m_vectext.append("控制板");
    m_vectext.append("算法");

    m_text_sortOne = new  QLabel(this);
    m_text_sortOne->setText(m_vectext.at(0));
    m_text_sortOne->setFont(font);
    m_color_sortOne = new  CDoubleButton(this);
    m_color_sortOne->setFixedSize(16,16);
    m_color_sortOne->setStyleSheet(strColor);
    m_color_sortOne->setFocusPolicy(Qt::NoFocus);

    m_text_sortTwo = new  QLabel(this);
    m_text_sortTwo->setText(m_vectext.at(1));
    m_text_sortTwo->setFont(font);
    m_color_sortTwo = new  CDoubleButton(this);
    m_color_sortTwo->setFixedSize(16,16);
    m_color_sortTwo->setStyleSheet(strColor);
    m_color_sortTwo->setFocusPolicy(Qt::NoFocus);

    m_text_sortThree = new  QLabel(this);
    m_text_sortThree->setText(m_vectext.at(2));
    m_text_sortThree->setFont(font);
    m_color_sortThree = new  CDoubleButton(this);
    m_color_sortThree->setFixedSize(16,16);
    m_color_sortThree->setStyleSheet(strColor);
    m_color_sortThree->setFocusPolicy(Qt::NoFocus);

    m_text_sortFour = new  QLabel(this);
    m_text_sortFour->setText(m_vectext.at(3));
    m_text_sortFour->setFont(font);
    m_color_sortFour = new  CDoubleButton(this);
    m_color_sortFour->setFixedSize(16,16);
    m_color_sortFour->setStyleSheet(strColor);
    m_color_sortFour->setFocusPolicy(Qt::NoFocus);

    /*m_text_weight = new  QLabel(this);
    m_text_weight->setText(tr("称重板子"));
    m_text_weight->setFont(font);
    m_color_weight = new  QLabel(this);
    m_color_weight->setFixedSize(16,16);
    m_color_weight->setStyleSheet(strColor);*/

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


//void CStateWid::setparamstate(ST_RUN_STATUS strstate)
//{
//    m_pLog->LogDebug(
//            "[%s][%s][%d] Run  State emType %d. Run  State iStatus:%d",
//            __FILE__, __FUNCTION__, __LINE__,(int)strstate.emType,strstate.iStatus);
//    if(strstate.emType == 3)
//    {
//        int IState = strstate.iStatus;
//        if(IState == 0)
//            m_color_thick->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
//        else if(IState == 1)
//            m_color_thick->setStyleSheet("border-radius:8px;background-color:orange");
//        else if(IState == 2)
//            m_color_thick->setStyleSheet("border-radius:8px;background-color:red");

//        strBhInfo = strstate.szStatusInfo;
//    }

//    else if(strstate.emType == 2)
//    {
//        int IState = strstate.iStatus;
//        if(IState == 0)
//            m_color_waste->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
//        else if(IState == 1)
//            m_color_waste->setStyleSheet("border-radius:8px;background-color:orange");
//        else if(IState == 2)
//            m_color_waste->setStyleSheet("border-radius:8px;background-color:red");

//        strFzInfo = strstate.szStatusInfo;
//    }

//    else if(strstate.emType == 1)
//    {
//        int IState = strstate.iStatus;
//        if(IState == 0)
//            m_color_rfid->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
//        else if(IState == 1)
//            m_color_rfid->setStyleSheet("border-radius:8px;background-color:orange");
//        else if(IState == 2)
//            m_color_rfid->setStyleSheet("border-radius:8px;background-color:red");

//        strService = strstate.szStatusInfo;
//    }

//    else if(strstate.emType == 4)
//    {
//        int IState = strstate.iStatus;
//        if(IState == 0)
//            m_color_stamp->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
//        else if(IState == 1)
//            m_color_stamp->setStyleSheet("border-radius:8px;background-color:orange");
//        else if(IState == 2)
//            m_color_stamp->setStyleSheet("border-radius:8px;background-color:red");

//        strGaiZInfo = strstate.szStatusInfo;
//    }

//    /*else if(strstate.emType == 4)
//    {
//        int IState = strstate.iStatus;
//        if(IState == 0)
//            m_color_weight->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
//        else if(IState == 1)
//            m_color_weight->setStyleSheet("border-radius:8px;background-color:orange");
//        else if(IState == 2)
//            m_color_weight->setStyleSheet("border-radius:8px;background-color:red");
//    }*/


//}

void CStateWid::setparamstate(ST_RUN_MONITOR_STATUS_INFO strstate)
{
//    m_pLog->LogDebug(
//            "[%s][%s][%d] setparamstate isRecover:%d codeId %d. errorInfo:%s .id:%d .name:%s",
//            __FILE__, __FUNCTION__, __LINE__,strstate.isRecover,strstate.codeId,strstate.errorInfo,strstate.id,strstate.name);

    QString codeid = QString::number(strstate.codeId);
    QString errorInfo = QString::fromUtf8(strstate.errorInfo);
    if(strstate.id == 100)
    {
        int IState = strstate.isRecover;
        if(IState == 1)
        {
            m_color_sortTwo->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
            emit sigShowErrorMsg(2,"","");
        }
        else if(IState == 0)
        {
            m_color_sortTwo->setStyleSheet("border-radius:8px;background-color:red");
            emit sigShowErrorMsg(2,codeid,errorInfo);
        }
    }

    else if(strstate.id == 500)
    {
        int IState = strstate.isRecover;
        if(IState == 1)
        {
            m_color_sortThree->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
            emit sigShowErrorMsg(1,"","");
        }
        else if(IState == 0)
        {
            m_color_sortThree->setStyleSheet("border-radius:8px;background-color:red");
            emit sigShowErrorMsg(1,codeid,errorInfo);
        }
    }

    else if(strstate.id == 200)
    {
        int IState = strstate.isRecover;
        if(IState == 1)
        {
            m_color_sortFour->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
            emit sigShowErrorMsg(3,"","");
        }
        else if(IState == 0)
        {
            m_color_sortFour->setStyleSheet("border-radius:8px;background-color:red");
            emit sigShowErrorMsg(3,codeid,errorInfo);
        }
    }

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
