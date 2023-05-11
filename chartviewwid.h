#ifndef CHARTVIEWWID_H
#define CHARTVIEWWID_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
QT_CHARTS_USE_NAMESPACE

#include <QDateTimeAxis>//时间坐标轴
#include <QValueAxis>//普通坐标轴
#include <QDateTime>
#include <QBoxLayout>

class ChartViewWid : public QWidget
{
public:
    explicit ChartViewWid(QWidget *parent = nullptr);
    void ElectricChange(int numa);
    Init(QString str_name);


private:
    QChart *qchart;
    QChartView *chartView;
    QLineSeries *ser0;//,*ser1,*ser2,*ser3;
    QDateTimeAxis *QaX;
    QValueAxis *QaY;
    QColor color;

};

#endif // CHARTVIEWWID_H
