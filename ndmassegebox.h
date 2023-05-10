#ifndef NDMASSEGEBOX_H
#define NDMASSEGEBOX_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <QCoreApplication>
#include "pushbutton.h"

class ndmassegebox : public QWidget
{
    Q_OBJECT
public:
    explicit ndmassegebox(QWidget *parent = nullptr);
    ~ndmassegebox();

   void Init();
   void setLabelText(QString text1, QString text2);
   void setType(int Itype);
   void SetButtonText(QString imgsrc,QPushButton* button);

   int m_Itype;


signals:
   void Clicked_btn_OK(int);
   void Clicked_btn_Cancel();

public slots:
   void okBtn_press();
   void cancleBtn_press();
   void closeBtn_press();

private:

    QLabel * m_titleLabel;
    PushButton *m_btn_closeBtn;

    QLabel *m_lbText;

    //QButtonGroup *m_btn_okcancel;

    QPushButton *m_btn_okBtn;
    QPushButton *m_btn_cancleBtn;

};

#endif // NDMASSEGEBOX_H
