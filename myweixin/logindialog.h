#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "myweixin.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
private slots:

    void on_pushButton_clicked();
    void showWeiChatWindow();

private:
    Ui::LoginDialog *ui;
    MyWeixin* weiChatWindow;

};

#endif // LOGINDIALOG_H
