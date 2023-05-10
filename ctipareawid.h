#ifndef CTIPAREAWID_H
#define CTIPAREAWID_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QDateTime>

class CTipAreaWid : public QWidget
{
    Q_OBJECT
public:
    explicit CTipAreaWid(QWidget *parent = nullptr);
    ~CTipAreaWid();
    void Init();

signals:
    void sigAllAuto(bool bAuto);

public slots:
    void slotStatusNotify(QString strInfo);
    void timerUpdate();
    void testlog();

private:
       QTextBrowser *m_StatusTextBrowser;
       QLabel *m_lb_time;

};

#endif // CTIPAREAWID_H
