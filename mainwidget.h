#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    int currentScreenWid;//整个主部件区域大小
    int currentScreenHei;//整个主部件区域大小

signals:

public slots:
};

#endif // MAINWIDGET_H
