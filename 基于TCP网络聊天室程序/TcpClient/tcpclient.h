#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHostAddress>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostInfo>

class TcpClient : public QDialog
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = 0,Qt::WindowFlags f=0);
    ~TcpClient();
private:
    QListWidget *m_listWidget;
    QLineEdit *m_senLineEdit;
    QPushButton *m_sendBtn;
    QLabel *m_userNameLabel;
    QLineEdit *m_userNameLineEdit;
    QLabel *m_serverIPLabel;
    QLineEdit *m_serverIPLineEdit;
    QLabel *m_portLabel;
    QLineEdit *m_portLineEdit;
    QPushButton *m_enterBtn;
    QGridLayout *mainLayout;
    bool status;
    int port;
    QHostAddress *serverIP;
    QString username;
    QTcpSocket *tcpsocket;
public slots:
    void slotEnter();
    void slotConnected();
    void slotDisconnectd();
    void dataReceived();
    void slotSend();


};

#endif // TCPCLIENT_H
