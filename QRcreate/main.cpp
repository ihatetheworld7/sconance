#include "qrcreate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRcreate w;
    w.show();

    return a.exec();
}
