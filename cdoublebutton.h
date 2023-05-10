#ifndef CDOUBLEBUTTON_H
#define CDOUBLEBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class CDoubleButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CDoubleButton(QWidget *parent = nullptr);
     ~CDoubleButton();

protected:
    void mouseDoubleClickEvent(QMouseEvent *ev); /*双击事件响应函数*/

signals:
    void DoubleClick();

private:
};

#endif // CDOUBLEBUTTON_H
