#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
class PushButton : public QPushButton
{

    Q_OBJECT

public:


    explicit PushButton(QWidget *parent = 0);


    ~PushButton();

    void loadPixmap(QString pic_name);
    void setBtnNum(int num);
    int getBtnNum();

protected:


    void enterEvent(QEvent *);


    void leaveEvent(QEvent *);

    void mousePressEvent(QMouseEvent *event);


    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);

private:

    //枚举按钮的几种状态
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    QPixmap pixmap;

    int btn_width; //按钮宽度
    int btn_height; //按钮高度
    bool mouse_press; //按钮左键是否按下

    int btn_num;
};

#endif // PUSHBUTTON_H
