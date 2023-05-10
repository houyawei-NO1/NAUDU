#include "pushbutton.h"

PushButton::PushButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
    btn_num = 0;
}

PushButton::~PushButton()
{

}

void PushButton::loadPixmap(QString pic_name)
{
    pixmap.load(pic_name);
    btn_width = pixmap.width()/4;
    btn_height = pixmap.height();
    setFixedSize(btn_width, btn_height);
}

void PushButton::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void PushButton::mouseReleaseEvent(QMouseEvent *)
{
    //若点击鼠标左键
    if(mouse_press)
    {
        mouse_press = false;
        status = ENTER;
        update();
        emit clicked();
    }
}

void PushButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void PushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
}

void PushButton::setBtnNum(int num)
{
    btn_num = num;
}

int PushButton::getBtnNum()
{
    return btn_num;
}
