#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionCar_triggered();
    connectDB();
    initData();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//
void MainWindow::on_actionCar_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label->setText("车辆管理");
}

void MainWindow::on_actionCala_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->cala);
    ui->label->setText("shell sum");
}
void MainWindow::connectDB()
{
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123");
    db.setDatabaseName("car");
    if(!db.open())
    {
        QMessageBox::warning(this,"数据库打开失败",db.lastError().text());
        return;
    }
}
void MainWindow::initData()
{
    QSqlQueryModel *querymodel=new QSqlQueryModel(this);
    querymodel->setQuery("select name from factory");
    ui->comboBoxFactory->setModel(querymodel);
    ui->labelLast->setText("0");
    ui->lineEditTotal->setEnabled(false);

}

void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1=="请选择厂家")
    {
        ui->comboBoxBrand->clear();
        ui->lineEditPrice->clear();
        ui->labelLast->setText("0");
        ui->lineEditTotal->clear();
        ui->spinBox->setValue(0);
    }
    else
    {
        ui->comboBoxBrand->clear();
       QSqlQuery query;
       QString sql=QString("select *from brand where factory='%1'").arg(arg1);
       query.exec(sql);
       while(query.next())
       {
           QString name=query.value(2).toString();
           ui->comboBoxBrand->addItem(name);
       }
    }
}

void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString sql=QString("select price,last from brand where factory='%1' and name='%2'")
            .arg(ui->comboBoxFactory->currentText())
            .arg(arg1);
    qDebug()<<sql;
    query.exec(sql);
    while(query.next())
    {
        int price=query.value("price").toInt();
        int last=query.value("last").toInt();
        ui->lineEditPrice->setText(QString::number(price));
        ui->lineEditTotal->setText(QString::number(last));


    }
}
