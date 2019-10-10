#ifndef MYWEIXIN_H
#define MYWEIXIN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include "filesrvdlg.h"
#include "filecntdlg.h"


class FileSrvDlg;
namespace Ui {
class MyWeixin;
}

enum ChatMsgType{ChatMsg,OnLine,OffLine,SfileName,RefFile};

class MyWeixin : public QDialog
{
    Q_OBJECT

public:
    explicit MyWeixin(QWidget *parent = 0);
    ~MyWeixin();
    void initMainWindow();
    void onLine(QString name,QString time);
    void offLine(QString name,QString time);
    void sendChatMsg(ChatMsgType msgType,QString rmtName = "");
//    void sendChatMsg(ChatMsgType msgType);
    QString getLocHostIp();
    QString getLocChatMsg();
    void recvFileName(QString name,QString hostip,QString rmtname,QString filename);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
//    void on_sendPushButton_clicked();
    void recvAndProcessChatMsg();
//    void on_searchPushButton_clicked();
    void getSfileName(QString);
//    void on_transPushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MyWeixin *ui;
    QUdpSocket *myUdpSocket;
    qint16 myUdpPort;
    QString myFileName;
    FileSrvDlg *myfsrv;
public:
    QString myname = "";
};

#endif // MYWEIXIN_H
