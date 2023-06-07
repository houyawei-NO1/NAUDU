#ifndef MENUBARWID_H
#define MENUBARWID_H

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QDebug>
#include <QProgressBar>
#include "pushbutton.h"
#include "toolbutton.h"

class MenuBarWid : public QWidget
{
    Q_OBJECT
public:
    explicit MenuBarWid(QWidget *parent = nullptr);
    void setupUi();
    ~MenuBarWid();
       void Init();
       void translateLanguage();
       void setFirBtnChecked();

   signals:
       void CurSelectPage(int);
       void showMin();
       void showMax();
       void closeWidget();


public slots:
       void slot_btnGroupClicked(int btnNum);
       void slotSetTotleNum();
       void rec_TotleNum(int num);
       void ReInit();

private:
   QWidget *widget=new QWidget(this);

    PushButton *m_pMin_button; //最小化
    PushButton *m_pMax_button; //最大化
    PushButton *m_pClose_button; //关闭

    QLabel *m_pVersion_title; //标题
    QButtonGroup *pushButtonGroup;


    QLabel* m_lbMode;
    QPushButton* m_btn_Mode;
    QHBoxLayout *modebtn_layout;
    QLabel* m_lbModeCircle;
    QLabel* lb_currentModeTitle;
    bool m_bMode;

    QLabel* m_lbTotleNum;
    QLabel* lb_TotleNum;
    int m_ItotleNum;
    QProgressBar *ProgressBar;
};

#endif // MENUBARWID_H
