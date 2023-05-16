#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canthread.h"
#include <QByteArray>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddDataToList(QStringList strList);
    QByteArray GetHexValue(QString str);
    char ConvertHexChar(char ch);
    void DataAnalysis(QStringList messageList);
    void ConnectDev();
    void ResetDev();
    void StaReInit();
signals:
    void signal_send(int,bool);
    void electric_send(int,int,int,int);
    void status_send(bool,bool,bool);
    void DataRec_sta();
    void UpdateUi();
private slots:
    void onGetProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel);
    void onBoardInfo(VCI_BOARD_INFO vbi);
    void on_pushButton_clicked();
    void on_sendBtn_clicked();
    void on_cleanListBtn_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void CheckEverySec();

private:
    Ui::MainWindow *ui;
    CANThread *canthread;
    bool iFlag_zuoyi,iFlag_lihe,iFlag_kongdang,iFlag_shuangbian,iFlag_pto_shineng,iFlag_pto_waibu,iFlag_tsq_weizhi,
         iFlag_tsq_diwei,iFlag_zhuche_zhongxiaotuo,iFlag_siqu,iFlag_tsq_jiaodu;
    bool iSta_Dev,iSta_CanInit,iSta_CanStart,iSta_RecIng;
//    NanDuWidget Widget;
};

#endif // MAINWINDOW_H
