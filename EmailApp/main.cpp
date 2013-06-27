#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Maximizes to screen once app is started
    w.showMaximized();
    
    return a.exec();
}
