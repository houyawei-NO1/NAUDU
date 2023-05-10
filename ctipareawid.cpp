#include "ctipareawid.h"

CTipAreaWid::CTipAreaWid(QWidget *parent) : QWidget(parent)
{
    Init();
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:rgb(43,48,70);");
    this->setMaximumHeight(40);
    this->setMinimumHeight(40);
}

CTipAreaWid::~CTipAreaWid()
{

}

void CTipAreaWid::Init()
{
    QHBoxLayout *pLay = new QHBoxLayout(this);
    m_StatusTextBrowser = new QTextBrowser(this);
    m_lb_time = new QLabel(this);
    m_lb_time->setMaximumWidth(240);
    m_lb_time->setStyleSheet("background-color:rgb(43,48,70);font-size:15px;color:white");
    m_lb_time->setAlignment(Qt::AlignCenter);
    pLay->addWidget(m_lb_time,2,Qt::AlignLeft);
    pLay->addWidget(m_StatusTextBrowser,8);

    //this->setLayout(pLay);
    setWindowFlags(Qt::FramelessWindowHint);
    m_StatusTextBrowser->setStyleSheet("border:0px;color:white");
    m_StatusTextBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_StatusTextBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_StatusTextBrowser->setVisible(true);

    /*QTextCursor text_cursor(ui->m_StatusTextBrowser->textCursor());//设置光标的位置
    text_cursor.movePosition(QTextCursor::End);
    ui->m_StatusTextBrowser->setTextCursor(text_cursor);*/

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}

void CTipAreaWid::slotStatusNotify(QString strInfo)
{
    QString strInfo1 = QString::fromLocal8Bit(strInfo.toLatin1().data());
    m_StatusTextBrowser->append(strInfo1);


    QTextCursor text_cursor(m_StatusTextBrowser->textCursor());//设置光标的位置
    text_cursor.movePosition(QTextCursor::End);
    m_StatusTextBrowser->setTextCursor(text_cursor);
}

void CTipAreaWid::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy/MM/dd hh:mm:ss");
    m_lb_time->setText(str);
}


void CTipAreaWid::testlog()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy/MM/dd hh:mm:ss");
    slotStatusNotify(str);
}
