#include "cdoublebutton.h"

CDoubleButton::CDoubleButton(QWidget *parent) : QPushButton(parent)
{

}
CDoubleButton::~CDoubleButton()
{

}

void CDoubleButton::mouseDoubleClickEvent(QMouseEvent * ev)
{
    if (ev->buttons() == Qt::LeftButton)
    {
        emit DoubleClick();
    }
}
