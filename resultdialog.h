#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>

class ResultDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ResultDialog(QWidget *parent = nullptr);

signals:

public slots:
private:
     QVBoxLayout *MainLayout;
};

#endif // RESULTDIALOG_H
