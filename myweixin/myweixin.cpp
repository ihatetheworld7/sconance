#include "myweixin.h"
#include "ui_myweixin.h"

MyWeixin::MyWeixin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyWeixin)
{
    ui->setupUi(this);
    initMainWindow();
}

MyWeixin::~MyWeixin()
{
    delete ui;
}
void MyWeixin::initMainWindow()
{
//    ui->userLabel->setText(myname);
    myUdpSocket=new QUdpSocket(this);
    myUdpPort=23232;
    myUdpSocket->bind(myUdpPort,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(myUdpSocket,SIGNAL(readyRead()),this,SLOT(recvAndProcessChatMsg()));
    myfsrv=new FileSrvDlg(this);
    connect(myfsrv,SIGNAL(sendFileName(QString)),this,SLOT(getSfileName(QString)));
}
//void MyWeixin::on_searchPushButton_clicked()
//{
//    myname = this->windowTitle();
//    ui->userLabel->setText(myname);
//    sendChatMsg(OnLine);
//}
void MyWeixin::sendChatMsg(ChatMsgType msgType, QString rmtName)
{
    QByteArray qba;
    QDataStream write(&qba,QIODevice::WriteOnly);
    QString locHostIp=getLocHostIp();
    QString locChatMsg=getLocChatMsg();
    write<<msgType<<myname;
    switch(msgType)
    {
    case ChatMsg:
        write<<locHostIp<<locChatMsg;
        break;
    case OnLine:
        write<<locHostIp;
    case OffLine:
        break;
    case SfileName:
        write<<locHostIp<<rmtName<<myFileName;
        break;
    case RefFile:
        write<<locHostIp<<rmtName;
        break;
    }
    myUdpSocket->writeDatagram(qba,qba.length(),QHostAddress::Broadcast,myUdpPort);
}
void MyWeixin::recvAndProcessChatMsg()
{
    while(myUdpSocket->hasPendingDatagrams())
    {
        QByteArray qba;
        qba.resize(myUdpSocket->pendingDatagramSize());
        myUdpSocket->readDatagram(qba.data(),qba.size());
        QDataStream read(&qba,QIODevice::ReadOnly);
        int msgType;
        read>>msgType;
        QString name,hostip,chatmsg,rname,fname;
        QString curtime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch(msgType)
        {
            case ChatMsg:{
                read>>name>>hostip>>chatmsg;
                ui->chatTextBrowser->setTextColor(Qt::darkGreen);
                ui->chatTextBrowser->setCurrentFont(QFont("Times New Roman",14));
                ui->chatTextBrowser->append("["+name+"]"+curtime);
                ui->chatTextBrowser->append(chatmsg);
                break;
        }
        case OnLine:
            read>>name>>hostip;
            onLine(name,curtime);
            break;
        case OffLine:
            read>>name;
            offLine(name,curtime);
            break;
        case SfileName:
            read>>name>>hostip>>rname>>fname;
            recvFileName(name,hostip,rname,fname);
            break;
        case RefFile:
            read>>name>>hostip>>rname;
            if(myname==rname) myfsrv->cntRefused();
            break;
        }
    }
}

void MyWeixin::onLine(QString name, QString time)
{
    bool notExist=ui->userListTabelWidget->findItems(name,Qt::MatchExactly).isEmpty();
    if(notExist)
    {
        QTableWidgetItem *newuser=new QTableWidgetItem(name);
        ui->userListTabelWidget->insertRow(0);
        ui->userListTabelWidget->setItem(0,0,newuser);
        ui->chatTextBrowser->setTextColor(Qt::gray);
        ui->chatTextBrowser->setCurrentFont(QFont("Times New Roman",12));
        ui->chatTextBrowser->append(tr("%1 %2 上线！").arg(time).arg(name));
        sendChatMsg(OnLine);
    }
}
void MyWeixin::offLine(QString name, QString time)
{
    int row=ui->userListTabelWidget->findItems(name,Qt::MatchExactly).first()->row();
    ui->userListTabelWidget->removeRow(row);
    ui->chatTextBrowser->setTextColor(Qt::gray);
    ui->chatTextBrowser->setCurrentFont(QFont("Times Now Roman",12));
    ui->chatTextBrowser->append(tr("%1 %2 离线！").arg(time).arg(name));
}
void MyWeixin::closeEvent(QCloseEvent *event)
{
    sendChatMsg(OffLine);
}
QString MyWeixin::getLocHostIp()
{
    QList<QHostAddress> addrlist=QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrlist) {
        if(addr.protocol()==QAbstractSocket::IPv4Protocol) return addr.toString();
    }
    return 0;
}

QString MyWeixin::getLocChatMsg()
{
    QString chatmsg=ui->charTextEdit->toHtml();
    ui->charTextEdit->clear();
    ui->charTextEdit->setFocus();
    return chatmsg;
}
//void MyWeixin::on_sendPushButton_clicked()
//{
//    sendChatMsg(ChatMsg);
//}

void MyWeixin::on_pushButton_2_clicked()
{
    sendChatMsg(ChatMsg);
}

void MyWeixin::on_pushButton_clicked()
{
    sendChatMsg(OnLine);
}
void MyWeixin::getSfileName(QString fname)
{
    myFileName=fname;
    int row=ui->userListTabelWidget->currentRow();
    QString rmtName=ui->userListTabelWidget->item(row,0)->text();
    sendChatMsg(SfileName,rmtName);
}

void MyWeixin::on_pushButton_3_clicked()
{
    if(ui->userListTabelWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0,tr("选择好友"),tr("请选择文件接收方！"),QMessageBox::Ok);
        return;
    }
    myfsrv->show();
}
void MyWeixin::recvFileName(QString name,QString hostip,QString rmtname,QString filename)
{
    if(myname==rmtname)
    {
        int result=QMessageBox::information(this,tr("收到文件"),tr("好友 %1 给您发文件：\r\n%2,是否接收？").arg(name).arg(filename),QMessageBox::Yes,QMessageBox::No);
        if(result==QMessageBox::Yes)
        {
            QString fname=QFileDialog::getSaveFileName(0,tr("保存"),filename);
            if(!fname.isEmpty())
            {
                FileCntDlg *fcnt=new FileCntDlg(this);
                fcnt->getLocPath(fname);
                fcnt->getSrvAddr(QHostAddress(hostip));
                fcnt->show();
            }
        }
        else
        {
            sendChatMsg(RefFile,name);
        }
    }
}
