#include "server.h"

Server::Server(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}
void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnect(int)),this,SLOT(slotDisconnected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    TcpClientSocketList.append(tcpClientSocket);
}
void Server::updateClients(QString msg, int length)
{
    emit updateSever(msg,length);
    for(int i=0;i<TcpClientSocketList.count();i++)
    {
        QTcpSocket *item=TcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length)
        {
            continue;
        }
    }
}
void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<TcpClientSocketList.count();i++)
    {
        QTcpSocket *item=TcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            TcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}
