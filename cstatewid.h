#ifndef CSTATEWID_H
#define CSTATEWID_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>
#include "cdoublebutton.h"


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
//    void setparamstate(ST_RUN_MONITOR_STATUS_INFO strstate);
   void click_on_BtnRfid();
   void click_on_BtnThick();
   void click_on_BtnWaste();
   void click_on_BtnStamp();
   void status_slot(bool,bool,bool);
   void DataRec_slot();

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
