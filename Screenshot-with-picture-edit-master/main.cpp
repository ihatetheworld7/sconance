#include "widget.h"
#include <QApplication>
#include "screen.h"
#include "controlwidget.h"
#include "myrect.h"
#include "widget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Screen s;
    Widget s;
    s.show();
    return a.exec();
}
