#include "chartviewwid.h"
#include <QMainWindow>
#include <QDebug>
ChartViewWid::ChartViewWid(QWidget *parent) : QWidget(parent)

{
    this->setStyleSheet("background-color:blue");
    qchart = new QChart();
//    qchart->setBackgroundBrush(QColor(43,48,70));

   //把chart放到容器里
   chartView = new QChartView(this);
   chartView->setStyleSheet("background-color:rgb(43,48,70)");
   chartView->resize(497,477);//宽，高

   //设置抗锯齿
   chartView->setChart(qchart);
   chartView->setRenderHint(QPainter::Antialiasing);

   //创建线
   ser0 = new QLineSeries;

}
ChartViewWid::Init(QString str_name)
{


   //设置名字
   ser0->setName(str_name);

   //放入charts里
   qchart->addSeries(ser0);
   qchart->setTitle(str_name);
   qchart->setTitleFont(QFont("Microsoft YaHei", 30, QFont::Bold));
   qchart->setTitleBrush(QColor(43,48,70));



   //创建x坐标
   QaX = new QDateTimeAxis;
   //格式
   QaX->setFormat("mm:ss");
   QaX->setTickCount(5);
   QaX->setTitleText("时间轴（分钟:秒）");
   QaX->setLabelsFont(QFont("Microsoft YaHei", 12, QFont::Bold));

   //创建y坐标
   QaY = new QValueAxis;
   //设置范围
   QaY->setRange(0,1400);
   QaY->setTickCount(15);
   QaY->setTitleText("电流值（mA）");
   QaY->setLabelsFont(QFont("Microsoft YaHei", 10, QFont::Bold));


   //将线条放入表中
   qchart->setAxisX(QaX,ser0);
   qchart->setAxisY(QaY,ser0);

   //初始化完成后取线条颜色
   color = ser0->color();
}

//数据更新
void ChartViewWid::ElectricChange(int num){

    //获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
     ser0->append(currentTime.toMSecsSinceEpoch(),num);
     if(num > 740 && num < 860)
     {
         ser0->setColor(QColor(67,207,124));
         qchart->setTitleBrush(QColor(67,207,124));
     }
        else
     {
         ser0->setColor(color);
         qchart->setTitleBrush(QColor(43,48,70));
     }


     qchart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-1*5));
     qchart->axisX()->setMax(QDateTime::currentDateTime().addSecs(1*1));


}
