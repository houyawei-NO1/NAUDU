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


   //创建x坐标
   QaX = new QDateTimeAxis;
   //格式
   QaX->setFormat("mm:ss");
   QaX->setTickCount(8);
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
    //    //获取随机数
    //    qsrand(QTime::currentTime().second());
    //    int rand  = qrand()%100;//获取0~10之间的数

    //获取初始化的qchart
//    QChart *qchart =(QChart *)ui->graphicsView->chart();

//    //获取之前的ser
//    QLineSeries *ser0 = (QLineSeries *)ui->graphicsView->chart()->series().at(0);
//    QLineSeries *ser1 = (QLineSeries *)ui->graphicsView->chart()->series().at(1);

    //更新数据
//    ser0->append(currentTime.toMSecsSinceEpoch(),cos(rand));
//    ser1->append(currentTime.toMSecsSinceEpoch(),sin(rand));

//    qchart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-1*30));
//    qchart->axisX()->setMax(QDateTime::currentDateTime().addSecs(1*30));

//    ui->label->setText(QTime::currentTime().toString("hh:mm:ss"));
     ser0->append(currentTime.toMSecsSinceEpoch(),num);
//     ser1->append(currentTime.toMSecsSinceEpoch(),numb);
//     ser2->append(currentTime.toMSecsSinceEpoch(),numc);
//     ser3->append(currentTime.toMSecsSinceEpoch(),numd);


     if(num > 740 && num < 860)  ser0->setColor(Qt::green);
        else ser0->setColor(color);


     qchart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-1*20));
     qchart->axisX()->setMax(QDateTime::currentDateTime().addSecs(1*5));


}
