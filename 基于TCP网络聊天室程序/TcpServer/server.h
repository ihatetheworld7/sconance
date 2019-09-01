#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QList>
#include "tcpclientsocket.h"
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=0);
    QList<TcpClientSocket*> TcpClientSocketList;
signals:
    void updateSever(QString,int);
public slots:
    void updateClients(QString,int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
