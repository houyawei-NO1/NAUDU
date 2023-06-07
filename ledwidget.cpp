#include "ledwidget.h"

LedWidget::LedWidget(QWidget *parent) : QWidget(parent)
{
    on_flag=false;
    off_flag=false;
    m_result=0;

    led_pic = new QLabel(this);
    led_name = new QLabel(this);
    led_layout = new QVBoxLayout();
    name_layout =  new QHBoxLayout();
    pic_layout =  new QHBoxLayout();
    on_layout = new QHBoxLayout();
    off_layout = new QHBoxLayout();
    final_layout = new QHBoxLayout();
    result_layout =  new QVBoxLayout();
    QString strColor="border-radius:8px;background-color:rgb(255,245,238)";
    QFont font;
    font.setPixelSize(13);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);

    QImage image;
    image.load(":/image/led_gray");
    led_pic->setPixmap(QPixmap::fromImage(image));
    led_pic->resize(QSize(image.width(),image.height()));

    m_text_on = new  QLabel(this);
    m_text_on->setText("开信号触发");
    m_text_on->setFont(font);
    m_text_on->setPalette(pe);
    m_color_on = new  CDoubleButton(this);
    m_color_on->setFixedSize(20,20);
    m_color_on->setStyleSheet(strColor);
    m_color_on->setFocusPolicy(Qt::NoFocus);
    on_layout->addWidget(m_color_on);
    on_layout->addWidget(m_text_on);

    m_text_off = new  QLabel(this);
    m_text_off->setText("关信号触发");
    m_text_off->setFont(font);
    m_text_off->setPalette(pe);
    m_color_off = new  CDoubleButton(this);
    m_color_off->setFixedSize(20,20);
    m_color_off->setStyleSheet(strColor);
    m_color_off->setFocusPolicy(Qt::NoFocus);
    off_layout->addWidget(m_color_off);
    off_layout->addWidget(m_text_off);

    m_text_final = new  QLabel(this);
    m_text_final->setText("功能测试通过");
    m_text_final->setFont(font);
    m_text_final->setPalette(pe);
    m_color_final = new  CDoubleButton(this);
    m_color_final->setFixedSize(20,20);
    m_color_final->setStyleSheet(strColor);
    m_color_final->setFocusPolicy(Qt::NoFocus);
    final_layout->addWidget(m_color_final);
    final_layout->addWidget(m_text_final);

    result_layout->addLayout(on_layout);
    result_layout->addLayout(off_layout);
    result_layout->addLayout(final_layout);

    pic_layout->addStretch();
    pic_layout->addWidget(led_pic);
    pic_layout->addLayout(result_layout);
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
     m_name  = str_name;
     led_name->setText(m_name);
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
     on_flag =false;
     off_flag = false;
     m_result = 0;
     m_color_on->setStyleSheet("border-radius:8px;background-color:rgb(255,245,238)");
     m_color_off->setStyleSheet("border-radius:8px;background-color:rgb(255,245,238)");
     m_color_final->setStyleSheet("border-radius:8px;background-color:rgb(255,245,238)");
}
LedWidget:: LedChange(bool status)
 {
     QImage image;
      if(status)
      {
          image.load(":/image/led_green");
          on_flag =true;
          m_color_on->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
      }
      else
      {
          image.load(":/image/led_red");
          off_flag =true;
          m_color_off->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
      }
      led_pic->setPixmap(QPixmap::fromImage(image));
      led_pic->resize(QSize(image.width(),image.height()));
      if(on_flag && off_flag)
      {
          m_result = 1;
          QTimer::singleShot(1 * 1000,this,[=]{
          m_color_final->setStyleSheet("border-radius:8px;background-color:rgb(67,207,124)");
          });
      }
 }
