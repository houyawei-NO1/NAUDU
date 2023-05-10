#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include  <QPainter>
#include <QLabel>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickedLabel(QWidget *parent = nullptr);
    ~ClickedLabel();

    int index;
    bool ButtonEffect;
    bool NeedSetBgPicure;

    QString PicPathEther;
    QString PicPathLeave;

    float Scalx;
    float Scaly;

    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

    void InitBgPicture();
    void SetTextAligntType(Qt::Alignment AligntStyle);
    void SetLabelHeight(int labelwid, int labelheight);

signals:
        void Clicked(ClickedLabel* clicked);
        void ClickedItemIndex(int, ClickedLabel*);
        void MouseMoveToItem(int,ClickedLabel*);

protected:
        void mouseReleaseEvent(QMouseEvent*);

};

#endif // CLICKEDLABEL_H
