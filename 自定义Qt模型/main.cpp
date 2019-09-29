#include "modelex.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModelEx modelEX;
    QTableView view;
    view.setModel(&modelEX);
    view.setWindowTitle("modelEX");
    view.resize(800,600);
    view.show();

    return a.exec();
}
