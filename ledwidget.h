#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "cdoublebutton.h"

class LedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LedWidget(QWidget *parent = nullptr);
    Init(QString str_name);
    ReInit();
    LedChange(bool status);
    int m_result;
    QString m_name;

signals:

public slots:

private:
    QLabel *led_pic;
    QLabel *led_name;
    QVBoxLayout *led_layout;
    QHBoxLayout *pic_layout;
    QHBoxLayout *name_layout;
    QHBoxLayout *on_layout;
    QHBoxLayout *off_layout;
    QHBoxLayout *final_layout;
    QVBoxLayout *result_layout;

    QLabel* m_text_on;
    CDoubleButton* m_color_on;
    bool on_flag;

    QLabel* m_text_off;
    CDoubleButton* m_color_off;
    bool off_flag;

    QLabel* m_text_final;
    CDoubleButton* m_color_final;

};

#endif // LEDWIDGET_H
