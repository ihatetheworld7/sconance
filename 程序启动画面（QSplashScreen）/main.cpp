#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix("D:\\Image\\2.jpg");
    QSplashScreen splash(pix);
    splash.show();
    a.processEvents();

    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
