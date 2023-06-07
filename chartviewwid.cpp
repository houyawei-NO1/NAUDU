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
   chartView->resize(505,430);//宽，高

   //设置抗锯齿
   chartView->setChart(qchart);
   chartView->setRenderHint(QPainter::Antialiasing);

   //创建线
   line_main = new QLineSeries;
   line_low = new QLineSeries;
   line_high = new QLineSeries;

   m_hege = 0;

}
ChartViewWid::Init(QString str_name)
{


    m_name = str_name;
   //设置名字
   line_main->setName(m_name);
   line_high->setName("正常电流区间");

   //放入charts里
   qchart->addSeries(line_main);
   qchart->addSeries(line_low);
   qchart->addSeries(line_high);


   qchart->setTitle(m_name);
   qchart->setTitleFont(QFont("Microsoft YaHei", 25, QFont::Bold));
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
   QaY->setTickCount(8);
   QaY->setTitleText("电流值（mA）");
   QaY->setLabelsFont(QFont("Microsoft YaHei", 10, QFont::Bold));
//   line_main[1]->setPen(QPen(Qt::blue,2,Qt::SolidLine));


   //将线条放入表中
   qchart->setAxisX(QaX,line_main);
   qchart->setAxisY(QaY,line_main);
   qchart->setAxisX(QaX,line_low);
   qchart->setAxisY(QaY,line_low);
   qchart->setAxisX(QaX,line_high);
   qchart->setAxisY(QaY,line_high);

   line_low->append(0,low_value);
   line_high->append(0,high_value);
   //初始化完成后取线条颜色
   color = line_main->color();
   line_low->setPen(QPen(QColor(233,150,122),2,Qt::SolidLine));
   line_high->setPen(QPen(QColor(233,150,122),2,Qt::SolidLine));

}

//数据更新
void ChartViewWid::ElectricChange(int num){


    //获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    line_main->append(currentTime.toMSecsSinceEpoch(),num);
    line_low->append(currentTime.toMSecsSinceEpoch(),low_value);
    line_high->append(currentTime.toMSecsSinceEpoch(),high_value);

    //
    if(num > low_value && num < high_value)
    {
     line_main->setColor(QColor(67,207,124));
     qchart->setTitleBrush(QColor(67,207,124));
//     qDebug()<<line_main->
     m_hege = 1;
    }
    else
    {
     line_main->setColor(color);
     qchart->setTitleBrush(QColor(43,48,70));
     m_hege = 0;
    }

/**
* @brief 注释
* @author houyawei
* @date 2023/05/18
* setTitleBrush()使图表标题颜色改变
*在qt5.6.3上面，三个以及三个以上图表同时使用函数setTitleBrush()，会使界面卡顿
*在qt5.9.3上面同时使用四个函数，功能正常。
*/

    qchart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-1*6));
    qchart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));


    if(line_main->count()>70) line_main->removePoints(0,3);
    if(line_low->count()>70) line_low->removePoints(0,3);
    if(line_high->count()>70) line_high->removePoints(0,3);


}
ChartViewWid::ReInit(){
    line_main->removePoints(0,line_main->count());
    m_hege = 0;
}
