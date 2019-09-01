#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle("TCP Server");
    resize(600,400);
    m_contentListWidget=new QListWidget;
    m_portLabel=new QLabel("端口:");
    m_portLineEdit=new QLineEdit;
    m_createBtn=new QPushButton("创建聊天室");
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(m_contentListWidget,0,0,1,2);
    mainLayout->addWidget(m_portLabel,1,0);
    mainLayout->addWidget(m_portLineEdit,1,1);
    mainLayout->addWidget(m_createBtn,2,0,1,2);
    port=8010;
    m_portLineEdit->setText(QString::number(port));
    connect(m_createBtn,SIGNAL(clicked(bool)),this,SLOT(slotCreateServer()));
}

TcpServer::~TcpServer()
{

}
void TcpServer::slotCreateServer()
{
    server=new Server(this,port);
    connect(server,SIGNAL(updateSever(QString,int)),this,SLOT(updateServer(QString,int)));
    m_createBtn->setEnabled(false);
}
void TcpServer::updateServer(QString msg, int length)
{
    m_contentListWidget->addItem(msg.left(length));
}
