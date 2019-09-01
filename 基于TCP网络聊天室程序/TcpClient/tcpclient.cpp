#include "tcpclient.h"

TcpClient::TcpClient(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent)
{
    setWindowTitle("TCP Client");
    m_listWidget=new QListWidget;
    m_senLineEdit= new QLineEdit;
    m_sendBtn=new QPushButton("发送");
    m_userNameLabel= new QLabel("用户名");
    m_userNameLineEdit= new QLineEdit;
    m_serverIPLabel=new QLabel("服务器地址：");
    m_serverIPLineEdit= new QLineEdit;
    m_portLabel=new QLabel("端口：");
    m_portLineEdit=new QLineEdit;
    m_enterBtn=new QPushButton("进入聊天室");
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(m_listWidget,0,0,1,2);
    mainLayout->addWidget(m_senLineEdit,1,0);
    mainLayout->addWidget(m_sendBtn,1,1);
    mainLayout->addWidget(m_userNameLabel,2,0);
    mainLayout->addWidget(m_userNameLineEdit,2,1);
    mainLayout->addWidget(m_serverIPLabel,3,0);
    mainLayout->addWidget(m_serverIPLineEdit,3,1);
    mainLayout->addWidget(m_portLabel,4,0);
    mainLayout->addWidget(m_portLineEdit,4,1);
    mainLayout->addWidget(m_enterBtn,5,0,1,2);
    status=false;
    port=8010;
    m_portLineEdit->setText(QString::number(port));
    serverIP=new QHostAddress();
    connect(m_enterBtn,SIGNAL(clicked(bool)),this,SLOT(slotEnter()));
    connect(m_sendBtn,SIGNAL(clicked(bool)),this,SLOT(slotSend()));
    m_sendBtn->setEnabled(false);
}

TcpClient::~TcpClient()
{

}
void TcpClient::slotEnter()
{
    if(!status)
    {
        QString ip=m_serverIPLineEdit->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
            return;
        }
        if(m_userNameLineEdit->text()=="")
        {
            QMessageBox::information(this,tr("error"),tr("User name error!"));
            return;
        }
        username=m_userNameLineEdit->text();
        tcpsocket=new QTcpSocket(this);
        connect(tcpsocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        connect(tcpsocket,SIGNAL(disconnected()),this,SLOT(slotDisconnectd()));
        connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
        tcpsocket->connectToHost(*serverIP,port);
        status=true;
    }
    else
    {
        int length=0;
        QString msg=username+tr(":Leave Chat Room");
        if((length=tcpsocket->write(msg.toLatin1(),msg.length()))!=msg.length())
        {
            return;
        }
        tcpsocket->disconnectFromHost();
        status=false;
    }
}
void TcpClient::slotConnected()
{
    m_sendBtn->setEnabled(true);
    m_enterBtn->setText("离开");
    int length=0;
    QString msg=username+tr(":Enter Char Room");
    if((length=tcpsocket->write(msg.toLatin1(),msg.length()))!=msg.length())
    {
        return;
    }
}
void TcpClient::slotSend()
{
    if(m_senLineEdit->text()=="")
    {
        return;
    }
    QString msg=username+":"+m_senLineEdit->text();
    tcpsocket->write(msg.toLatin1(),msg.length());
    m_senLineEdit->clear();
}
void TcpClient::slotDisconnectd()
{
    m_sendBtn->setEnabled(false);
    m_enterBtn->setText("进入聊天室");
}
void TcpClient::dataReceived()
{
    while(tcpsocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpsocket->bytesAvailable());
        tcpsocket->read(datagram.data(),datagram.size());
        QString msg=datagram.data();
        m_listWidget->addItem(msg.left(datagram.size()));
    }
}
