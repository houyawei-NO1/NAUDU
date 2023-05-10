#ifndef CSTATEWID_H
#define CSTATEWID_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "cdoublebutton.h"

typedef struct __ST_RUN_MONITOR_STATUS_INFO__
{
public:
    unsigned short codeId;//子错误码
    unsigned short errorLever;
    unsigned short id;
    bool isRecover; // 0x00  异常触发  0x01异常恢复
    char errorInfo[128];
    char name[64];   //模块名称
    bool operator< (const __ST_RUN_MONITOR_STATUS_INFO__& A)const{
        if(this->id < A.id)
            return true;
        else if(this->codeId < A.codeId)
            return true;
        else
            return false;
    }

}ST_RUN_MONITOR_STATUS_INFO;

class CStateWid : public QWidget
{
    Q_OBJECT
public:
    explicit CStateWid(QWidget *parent = nullptr);
    ~CStateWid();
    void Init();

signals:
    void sigBtnClick(int,QString);
    void sigShowErrorMsg(int,QString,QString);
public slots:
    void setparamstate(ST_RUN_MONITOR_STATUS_INFO strstate);
   void click_on_BtnRfid();
   void click_on_BtnThick();
   void click_on_BtnWaste();
   void click_on_BtnStamp();

private:
       QLabel* m_text_sortOne;
       CDoubleButton* m_color_sortOne;

       QLabel* m_text_sortTwo;
       CDoubleButton* m_color_sortTwo;

       QLabel* m_text_sortThree;
       CDoubleButton* m_color_sortThree;

       QLabel* m_text_sortFour;
       CDoubleButton* m_color_sortFour;

       //QLabel* m_text_weight;
       //QLabel* m_color_weight;

       QString strService;
       QString strBhInfo;
       QString strFzInfo;
       QString strGaiZInfo;

       QVector<QString> m_vectext;


};


#endif // CSTATEWID_H
