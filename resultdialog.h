/**
* @brief 注释
* @author houyawei
* @date 2023/05/23
*主窗口部件结果显示，未合格产品
*
*/
#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QStringList>
#include <QDebug>

class ResultDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ResultDialog(QWidget *parent = nullptr);

signals:

public slots:
    void rec_BuhegeXiangmu(QString);
private:
     QVBoxLayout *MainLayout;
     QProgressBar *ProgressBar;
     QLabel *ResultLabel;
     QStringList StringList;
};

#endif // RESULTDIALOG_H
