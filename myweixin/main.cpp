#include "myweixin.h"
#include <QApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MyWeixin w;
//    w.show();
    LoginDialog loginDlg;
    loginDlg.show();

    return a.exec();
}
