#include "mainwindow.h"
#include "nanduwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
     NanDuWidget Widget;
     Widget.show();



    return a.exec();
}
