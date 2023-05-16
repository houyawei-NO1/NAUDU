#include "ledwidget.h"

LedWidget::LedWidget(QWidget *parent) : QWidget(parent)
{

    led_pic = new QLabel(this);
    led_name = new QLabel(this);
    led_layout = new QVBoxLayout();
    name_layout =  new QHBoxLayout();
    pic_layout =  new QHBoxLayout();

    QImage image;
    image.load(":/image/led_gray");
    led_pic->setPixmap(QPixmap::fromImage(image));
    led_pic->resize(QSize(image.width(),image.height()));
    pic_layout->addStretch();
    pic_layout->addWidget(led_pic);
    pic_layout->addStretch();

    led_name->setText("初始化");
    led_name->setStyleSheet("color:white;font:40px");
    name_layout->addStretch();
    name_layout->addWidget(led_name);
    name_layout->addStretch();

//    led_layout->addStretch();
    led_layout->addLayout(pic_layout);
    led_layout->addStretch();
    led_layout->addLayout(name_layout);
    led_layout->addStretch();

    setLayout(led_layout);

}

LedWidget::Init(QString str_name)
 {
     led_name->setText(str_name);
     QImage image;
     image.load(":/image/led_gray");
     led_pic->setPixmap(QPixmap::fromImage(image));
     led_pic->resize(QSize(image.width(),image.height()));
 }
LedWidget::ReInit()
{
    QImage image;
    image.load(":/image/led_gray");
    led_pic->setPixmap(QPixmap::fromImage(image));
//    led_pic->resize(QSize(image.width(),image.height()));
}
LedWidget:: LedChange(bool status)
 {
     QImage image;
      if(status)
      {
          image.load(":/image/led_green");
      }
      else
      {
          image.load(":/image/led_red");
      }
      led_pic->setPixmap(QPixmap::fromImage(image));
      led_pic->resize(QSize(image.width(),image.height()));
 }
