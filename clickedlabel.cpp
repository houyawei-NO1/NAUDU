#include "clickedlabel.h"

ClickedLabel::ClickedLabel(QWidget *parent) : QLabel(parent)
{
    ButtonEffect = false;
        NeedSetBgPicure = false;
        Scalx = 1;
        Scaly = 1;
        this->setAlignment(Qt::AlignCenter);
}

ClickedLabel::~ClickedLabel()
{
}

void ClickedLabel::SetTextAligntType(Qt::Alignment AligntStyle)
{
    this->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *evt)
{
    emit ClickedItemIndex(index, this);
    emit Clicked(this);
}

void ClickedLabel::SetLabelHeight(int labelwid,int labelheight)
{
    this->setFixedSize(labelwid,labelheight);
}


void ClickedLabel::InitBgPicture()
{
    QPixmap map(PicPathLeave);
    map = map.scaled(map.width() * Scalx, map.height() * Scaly, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(map);
}


void ClickedLabel::enterEvent(QEvent *e)
{
    if (ButtonEffect)
    {
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(14);
        effect->setColor(Qt::white);
        effect->setOffset(0, 0);
        this->setGraphicsEffect(effect);
    }

    if (NeedSetBgPicure)
    {
        QPixmap map(PicPathEther);
        map = map.scaled(map.width() * Scalx, map.height() * Scaly, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        this->setPixmap(map);
    }

    emit MouseMoveToItem(index, this);
}

void ClickedLabel::leaveEvent(QEvent *e)
{
    if (ButtonEffect)
    {
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(0);
        effect->setColor(Qt::gray);
        effect->setOffset(0, 0);
        this->setGraphicsEffect(effect);

    }

    if (NeedSetBgPicure)
    {
        QPixmap map(PicPathLeave);
        map = map.scaled(map.width() * Scalx, map.height() * Scaly, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        this->setPixmap(map);
    }
}
