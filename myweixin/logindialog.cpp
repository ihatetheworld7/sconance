#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->userLineEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    showWeiChatWindow();
}
void LoginDialog::showWeiChatWindow()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123");
    db.setDatabaseName("user");
    if(!db.open())
    {
        QMessageBox::warning(this,"数据库打开失败",db.lastError().text());
        return;
    }

    QSqlQuery query;
    QString namesql=QString("select username from `user_table` where username='%1'")
            .arg(ui->userLineEdit->text());
    query.exec(namesql);
    if(!query.next())
    {
        QMessageBox::warning(0,tr("提示"),tr("用户名错误，请重新输入！"));
        return;
    }
    QString strpwd=ui->pwdLineEdit->text();
    QString sql=QString("select password from `user_table` where username='%1'")
            .arg(ui->userLineEdit->text());
    query.exec(sql);
    while(query.next())
    {
        QString password=query.value("password").toString();
        if(password==strpwd)
        {
            weiChatWindow=new MyWeixin(0);
            weiChatWindow->myname=ui->userLineEdit->text();
            weiChatWindow->setWindowTitle(ui->userLineEdit->text());
            weiChatWindow->show();
            this->hide();
        }
        else
        {
            QMessageBox::warning(0,tr("提示"),tr("密码错误！请重新输入！"));
        }
    }
}
