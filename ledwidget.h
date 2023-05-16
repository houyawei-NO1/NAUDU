#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class LedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LedWidget(QWidget *parent = nullptr);
    Init(QString str_name);
    ReInit();
    LedChange(bool status);

signals:

public slots:

private:
    QLabel *led_pic;
    QLabel *led_name;
    QVBoxLayout *led_layout;
    QHBoxLayout *pic_layout;
    QHBoxLayout *name_layout;
};

#endif // LEDWIDGET_H
