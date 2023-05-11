#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList listHeader;
    listHeader << "系统时间" << "时间标识" << "时间标识(s)" << "CAN通道" << "传输方向" << "ID号" << "帧类型" << "帧格式" << "长度" << "数据";

    ui->comboBox_3->setCurrentIndex(8);

    ui->tableWidget->setColumnCount(listHeader.count());
    ui->tableWidget->setHorizontalHeaderLabels(listHeader);

    ui->tableWidget->setColumnWidth(0,120);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,120);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,80);
    ui->tableWidget->setColumnWidth(5,120);
    ui->tableWidget->setColumnWidth(6,90);
    ui->tableWidget->setColumnWidth(7,90);
    ui->tableWidget->setColumnWidth(8,80);
    ui->tableWidget->setColumnWidth(9,250);

    //for(int i = 0;i < 9;i ++)
    //    ui->tableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    canthread = new CANThread();
    connect(canthread,&CANThread::getProtocolData,this,&MainWindow::onGetProtocolData);
    connect(canthread,&CANThread::boardInfo,this,&MainWindow::onBoardInfo);

    iFlag_zuoyi,iFlag_lihe,iFlag_kongdang,iFlag_shuangbian,iFlag_pto_shineng,iFlag_pto_waibu,iFlag_tsq_weizhi,
    iFlag_tsq_diwei,iFlag_siqu,iFlag_tsq_jiaodu = false;
    iFlag_zhuche_zhongxiaotuo = true;



//    Widget.show();
//    emit signal_send(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddDataToList(QStringList strList)
{
    if(!ui->checkBox_4->checkState())
        return;
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    for(int i = 0; i < strList.count();i ++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(strList.at(i),0);
        ui->tableWidget->setItem(row, i, item);
        if(i != strList.count() - 1)
            ui->tableWidget->item(row,i)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    }
    ui->tableWidget->scrollToBottom();
}
void MainWindow::onGetProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel)
{
    QStringList messageList;
    QString str;
    for(unsigned int i = 0;i < dwRel;i ++)
    {
        messageList.clear();
        messageList << QTime::currentTime().toString("hh:mm:ss zzz");//时间
        if(vci[i].TimeFlag == 1)
        {
            messageList << "0x" + QString("%1").arg(vci[i].TimeStamp,8,16,QChar('0')).toUpper();//时间
            messageList << QString("%1").arg(QVariant(vci[i].TimeStamp * 0.1).toUInt(),8,10,QChar('0'));//时间
        }
        else
        {
            messageList << "无";//时间
            messageList << "无";//时间
        }
        messageList << "CH" + QString::number(channel);
        messageList << "接收";//收发
        messageList << "0x" + QString("%1").arg(vci[i].ID,8,16,QChar('0')).toUpper();//ID
        messageList << ((vci[i].RemoteFlag == 1) ? "远程帧" : "数据帧");//类型
        messageList << ((vci[i].ExternFlag == 1) ? "扩展帧" : "标准帧");//Frame
        QString str = "";
        if(vci[i].RemoteFlag == 0)//数据帧显示数据
        {
            messageList << "0x" + QString::number(vci[i].DataLen,16).toUpper();//长度
            str = "x| ";

            for(int j = 0;j < vci[i].DataLen;j ++)
                str += QString("%1 ").arg(vci[i].Data[j],2,16,QChar('0')).toUpper();//QString::number(recvCANData[i].frame.data[j],16) + " ";

        }
        else
            messageList << "0x0";//长度
        messageList << str;//数据
        /*
        //listHeader << "时间"  << "收/发" << "ID" << "Frame" << "类型" << "长度" << "数据";
        messageList.clear();
        messageList << QString::number(channel);
        messageList << "收";//收发
        messageList << "0x" + QString("%1").arg(vci[i].ID,8,16,QChar('0'));//ID
        messageList << ((vci[i].ExternFlag == 1) ? "扩展帧" : "标准帧");//Frame
        messageList << ((vci[i].RemoteFlag == 1) ? "远程帧" : "数据帧");//类型
        str = "";
        if(vci[i].RemoteFlag == 0)//数据帧显示数据
        {
            messageList << QString::number(vci[i].DataLen);//长度
            for(int j = 0;j < vci[i].DataLen;j ++)
                str += QString("%1 ").arg(vci[i].Data[j],2,16,QChar('0'));//QString::number(recvCANData[i].frame.data[j],16) + " ";
        }
        else
            messageList << "0";//长度
        messageList << str;//数据
        */

        AddDataToList(messageList);
        DataAnalysis(messageList);

    }
}

QString versionStr(USHORT ver)
{
    return "V" + QString::number((ver & 0x0FFF) /0x100,16).toUpper() + "." + QString("%1 ").arg((ver & 0x0FFF) % 0x100,2,16,QChar('0')).toUpper();
}

void MainWindow::onBoardInfo(VCI_BOARD_INFO vbi)
{
    ui->label_9->setText(QString::number(vbi.can_Num));
    ui->label_10->setText(versionStr(vbi.hw_Version));
    ui->label_12->setText(versionStr(vbi.in_Version));
    ui->label_13->setText(QString::number(vbi.irq_Num));
}

void MainWindow::on_pushButton_clicked()//打开
{
//    emit signal_send(1);
    if(ui->pushButton->text() == tr("打开设备"))
    {
        UINT baundRate = 0;
        if(ui->comboBox_3->currentText().indexOf("Kbps") != -1)
            baundRate = ui->comboBox_3->currentText().remove("Kbps").toUInt();
        else
            baundRate = QVariant(ui->comboBox_3->currentText().remove("Mbps").toFloat()).toUInt();
        bool dev = canthread->openDevice(4,//QVariant(ui->comboBox->currentIndex()).toUInt(),
                                      QVariant(ui->comboBox_2->currentIndex()).toUInt(),
                                      baundRate);
        if(dev == true)
        {
            ui->comboBox->setEnabled(false);
            ui->comboBox_2->setEnabled(false);
            ui->comboBox_3->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton->setText(tr("关闭设备"));
        }
        else
            QMessageBox::warning(this,"警告","打开设备失败！");
    }
    else if(ui->pushButton->text() == tr("关闭设备"))
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->sendBtn->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton->setText(tr("打开设备"));
        canthread->stop();
        canthread->closeDevice();
    }
}

void MainWindow::on_sendBtn_clicked()
{
    if(ui->comboBox_6->currentIndex() == 0)//标准帧，ID 范围0-0x7FF
    {
        if(ui->sendIDEdit->text().toInt(Q_NULLPTR,16) > 0x7FF)
        {
            QMessageBox::warning(this,"警告","发送失败，标准帧ID范围为0~0x7FF！");
            return;
        }
    }
    else
    {
        if(ui->sendIDEdit->text().toInt(Q_NULLPTR,16) > 0x1FFFFFFF)
        {
            QMessageBox::warning(this,"警告","发送失败，扩展帧ID范围为0~0x1FFFFFFF！");
            return;
        }
    }
    QStringList strList = ui->sendDataEdit->text().split(" ");
    unsigned char data[8];
    memset(data,0,8);
    UINT dlc = 0;
    dlc = strList.count() > 8 ? 8 : strList.count();
    for(int i = 0;i < dlc;i ++)
        data[i] = strList.at(i).toInt(Q_NULLPTR,16);
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                           QVariant(ui->sendIDEdit->text().toInt(Q_NULLPTR,16)).toUInt(),
                           ui->comboBox_5->currentIndex(),//标准帧
                           ui->comboBox_6->currentIndex(),//数据帧
                           data,dlc))
    {//发送成功，打印数据
        QStringList messageList;

        messageList.clear();
        messageList << QTime::currentTime().toString("hh:mm:ss zzz");//时间
        messageList << "无";//时间
        messageList << "无";//时间
        messageList << "CH" + QString::number(QVariant(ui->comboBox_4->currentIndex()).toUInt());
        messageList << "发送";//收发
        messageList << "0x" + ui->sendIDEdit->text().toUpper();//ID
        messageList << ((ui->comboBox_5->currentIndex() == 0) ? "数据帧" : "远程帧");//类型
        messageList << ((ui->comboBox_6->currentIndex() == 0) ? "标准帧" : "扩展帧");//Frame
        QString str = "";
        if(ui->comboBox_5->currentIndex() == 0)//数据帧显示数据
        {
            messageList << "0x" + QString::number(dlc,16).toUpper();//长度
            str = "x| ";
            for(int j = 0;j < dlc;j ++)
                str += QString("%1 ").arg((unsigned char)data[j],2,16,QChar('0')).toUpper();//QString::number((unsigned char)data[j],16) + " ";
        }
        else
            messageList << "0x0";//长度
        messageList << str;//数据
        AddDataToList(messageList);
    }
    else
        QMessageBox::warning(this,"警告","数据发送失败！");
}

void MainWindow::on_cleanListBtn_clicked()
{
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_4_clicked()//复位
{
    if(canthread->reSetCAN())
    {
        ui->pushButton_4->setEnabled(false);
        ui->sendBtn->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
    }
    else
        QMessageBox::warning(this,"警告","CAN复位失败！");
}

void MainWindow::on_pushButton_2_clicked()//初始化
{
    if(canthread->initCAN())
    {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
    }
    else
        QMessageBox::warning(this,"警告","CAN初始化失败！");
}

void MainWindow::on_pushButton_3_clicked()//启动
{
    if(canthread->startCAN())
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(true);
        ui->sendBtn->setEnabled(true);
        canthread->start();
    }
    else
        QMessageBox::warning(this,"警告","CAN启动失败！");
}

QByteArray MainWindow::GetHexValue(QString str)
//直接将字符串，按照每两个字符分隔，然后转换成16进制发送。把Qstring类型转成QByteArray ，然后发送出去。
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
char MainWindow::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))      //限定字符0-9
         return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F')) //限定字符A-F
         return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f')) //限定字符a-f
         return ch-'a'+10;
    else return (-1);
}

void MainWindow::DataAnalysis(QStringList messageList)
{

    if(messageList.at(5)== "0x18FF2053")
        {
//                qDebug()<<"messageList.size()"<<messageList.size()<<endl
//                       <<"messageList:"<<messageList<<endl
//                      <<"messageList.at(5)"<<messageList.at(5)<<endl
//                         <<"messageList.at(9)"<<messageList.at(9)<<endl;
            QString string_data;
            string_data = messageList.at(9);
            string_data.remove("x|").remove(" ").simplified();
            QString string_data_head = string_data.mid(0,8);
            QString string_data_tail = string_data.mid(8,8);

            bool ok;
            quint32 hex_data_head = string_data_head.toUInt(&ok,16);
            quint32 hex_data_tail = string_data_tail.toUInt(&ok,16);
            quint32 and_result;

//                qDebug()<<"接收到的数据："<<string_data_head.toLatin1()
//                        <<"前四个字节hex_data_head:"<<QString::number(hex_data_head ,16).toUpper()<<endl;
//                qDebug()<<"接收到的数据："<<string_data_tail.toLatin1()
//                        <<"后四个字节hex_data_head:"<<QString::number(hex_data_tail ,16).toUpper()<<endl;

//                qDebug()<<"and_result"<<QString::number(and_result ,16).toUpper()<<endl;

            //座椅开关检测
            and_result =  hex_data_head & 0x01000000 ;
            if (and_result == 0x01000000 && iFlag_zuoyi == false)
            {

                iFlag_zuoyi = true ;
                emit signal_send(0,iFlag_zuoyi);
                qDebug() <<"座椅开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_zuoyi == true)
            {
                iFlag_zuoyi = false ;
                emit signal_send(0,iFlag_zuoyi);
                qDebug() <<"座椅关"<<endl;
            }
             //离合器开关检测
            and_result =  hex_data_head & 0x04000000 ;
            if (and_result == 0x04000000 && iFlag_lihe == false)
            {

                iFlag_lihe = true ;
                emit signal_send(1,iFlag_lihe);
                qDebug() <<"离合开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_lihe == true)
            {
                iFlag_lihe = false ;
                emit signal_send(1,iFlag_lihe);
                qDebug() <<"离合关"<<endl;
            }
            //空挡开关检测
            and_result =  hex_data_head & 0x50000000 ;
            if (and_result == 0x50000000 && iFlag_kongdang == false)
            {

               iFlag_kongdang = true ;
               emit signal_send(3,iFlag_kongdang);
               qDebug() <<"空挡开"<<endl;
            }
            else if (and_result == 0x10000000 && iFlag_kongdang == true)
            {
               iFlag_kongdang = false ;
               emit signal_send(3,iFlag_kongdang);
               qDebug() <<"空挡关"<<endl;
            }
            //双边制动开关检测
            and_result =  hex_data_head & 0x00010000 ;
            if (and_result == 0x00010000 && iFlag_shuangbian == false)
            {

              iFlag_shuangbian = true ;
              emit signal_send(4,iFlag_shuangbian);
              qDebug() <<"双边制动开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_shuangbian == true)
            {
              iFlag_shuangbian = false ;
               emit signal_send(4,iFlag_shuangbian);
              qDebug() <<"双边制动关"<<endl;
            }
            //pto使能开关检测
            and_result =  hex_data_head & 0x00040000 ;
            if (and_result == 0x00040000 && iFlag_pto_shineng == false)
            {

             iFlag_pto_shineng = true ;
             emit signal_send(5,iFlag_pto_shineng);
             qDebug() <<"pto使能开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_pto_shineng == true)
            {
             iFlag_pto_shineng = false ;
              emit signal_send(5,iFlag_pto_shineng);
             qDebug() <<"pto使能关"<<endl;
            }
            //pto外部开关检测
            and_result =  hex_data_head & 0x00100000 ;
            if (and_result == 0x00100000 && iFlag_pto_waibu == false)
            {

            iFlag_pto_waibu = true ;
             emit signal_send(6,iFlag_pto_waibu);
            qDebug() <<"pto外部开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_pto_waibu == true)
            {
            iFlag_pto_waibu = false ;
            emit signal_send(6,iFlag_pto_waibu);
            qDebug() <<"pto外部关"<<endl;
            }
            //提升器位置功能检测
            and_result =  hex_data_head & 0x00400000 ;
            if (and_result == 0x00400000 && iFlag_tsq_weizhi == false)
            {

            iFlag_tsq_weizhi = true ;
            emit signal_send(7,iFlag_tsq_weizhi);
            qDebug() <<"提升器位置变化"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_tsq_weizhi == true)
            {
            iFlag_tsq_weizhi = false ;
            emit signal_send(7,iFlag_tsq_weizhi);
            qDebug() <<"提升器位置恢复"<<endl;
            }

            //提升器低位功能检测
            and_result =  hex_data_head & 0x00000100 ;
            if (and_result == 0x00000100 && iFlag_tsq_diwei == false)
            {

            iFlag_tsq_diwei = true ;
            emit signal_send(8,iFlag_tsq_diwei);
            qDebug() <<"提升器低位开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_tsq_diwei == true)
            {
            iFlag_tsq_diwei = false ;
             emit signal_send(8,iFlag_tsq_diwei);
            qDebug() <<"提升器低位关"<<endl;
            }
            //中拖制动开关检测
            and_result =  hex_data_head & 0x00000400 ;
            if (and_result == 0x00000400 && iFlag_zhuche_zhongxiaotuo == true)
            {

            iFlag_zhuche_zhongxiaotuo = false ;
            emit signal_send(9,iFlag_zhuche_zhongxiaotuo);
            qDebug() <<"中拖制动关"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_zhuche_zhongxiaotuo == false)
            {
            iFlag_zhuche_zhongxiaotuo = true ;
            emit signal_send(9,iFlag_zhuche_zhongxiaotuo);
            qDebug() <<"中拖制动开"<<endl;
            }
            //四驱使能开关检测
            and_result =  hex_data_head & 0x00001000 ;
            if (and_result == 0x00001000 && iFlag_siqu == false)
            {

            iFlag_siqu = true ;
            emit signal_send(10,iFlag_siqu);
            qDebug() <<"四驱使能开"<<endl;
            }
            else if (and_result == 0x00000000 && iFlag_siqu == true)
            {
            iFlag_siqu = false ;
             emit signal_send(10,iFlag_siqu);
            qDebug() <<"四驱使能关"<<endl;
            }
            //提升器位置角度功能检测
            and_result =  hex_data_tail & 0xfa000000 ;
            if (and_result == 0x00000000 && iFlag_tsq_jiaodu == false)
            {

            iFlag_tsq_jiaodu = true ;
             emit signal_send(11,iFlag_tsq_jiaodu);
            qDebug() <<"提升器位置角度变化"<<endl;
            }
            else if (and_result == 0xfa000000 && iFlag_tsq_jiaodu == true)
            {
            iFlag_tsq_jiaodu = false ;
            emit signal_send(11,iFlag_tsq_jiaodu);
            qDebug() <<"提升器位置角度恢复默认"<<endl;
            }



        }

    if(messageList.at(5)=="0x18FFB253")
       {
        QString string_data;
        string_data = messageList.at(9);
        string_data.remove("x|").remove(" ").simplified();
        QString string_data_1 = string_data.mid(0,2);
        QString string_data_2 = string_data.mid(2,2);
        QString string_data_3 = string_data.mid(4,2);
        QString string_data_4 = string_data.mid(6,2);

        bool ok;
        int hex_data_1 = string_data_1.toInt(&ok,16) * 10;
        int hex_data_2 = string_data_2.toInt(&ok,16) * 10;
        int hex_data_3 = string_data_3.toInt(&ok,16) * 10;
        int hex_data_4 = string_data_4.toInt(&ok,16) * 10;

//        qDebug()<<"接收到的数据："<<string_data_1.toLatin1()<<endl
//                <<"四驱电磁阀电流: "<<hex_data_1<<"mA"<<endl
//                <<"启动电磁阀电流: "<<hex_data_2<<"mA"<<endl
//                <<"蜂鸣器电磁阀电流: "<<hex_data_3<<"mA"<<endl
//                <<"pto电磁阀电流: "<<hex_data_4<<"mA"<<endl;
        emit electric_send(hex_data_2,hex_data_1,hex_data_3,hex_data_4);
       }
}

//设备连接
void MainWindow::ConnectDev()
{
    on_pushButton_clicked();//打开
    on_pushButton_2_clicked();//初始化
    on_pushButton_3_clicked();//启动
}
//设备复位
void MainWindow::ResetDev()
{
    on_pushButton_4_clicked();//复位
//    on_pushButton_clicked();//关闭
//    on_pushButton_clicked();//打开
//    on_pushButton_2_clicked();//初始化
    on_pushButton_3_clicked();//启动
}

