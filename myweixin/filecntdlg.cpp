#include "filecntdlg.h"
#include "ui_filecntdlg.h"

FileCntDlg::FileCntDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileCntDlg)
{
    ui->setupUi(this);
    myCntSocket=new QTcpSocket(this);
    mySrvport=5555;
    connect(myCntSocket,SIGNAL(readyRead()),this,SLOT(readChatMsg()));
    myFileNameSize=0;
    myTotalBytes=0;
    myRcveBytes=0;
}

FileCntDlg::~FileCntDlg()
{
    delete ui;
}

void FileCntDlg::on_pushButton_clicked()
{
    myCntSocket->abort();
    myLocPathFile->close();
    close();

}
void FileCntDlg::closeEvent(QCloseEvent *)
{
    on_pushButton_clicked();
}

void FileCntDlg::createConnToSrv()
{
    myBlockSize=0;
    myCntSocket->abort();
    myCntSocket->connectToHost(mySrvAddr,mySrvport);
    mytime.start();
}

void FileCntDlg::readChatMsg()
{
    QDataStream in(myCntSocket);
    in.setVersion(QDataStream::Qt_5_9);
    float usedTime=mytime.elapsed();
    if(myRcveBytes<=sizeof(qint64)*2);
    {
        if((myCntSocket->bytesAvailable()>=sizeof(qint64)*2) && (myFileNameSize==0))
        {
            in>>myTotalBytes>>myFileNameSize;
            myRcveBytes+=sizeof(qint64)*2;
        }
        if((myCntSocket->bytesAvailable()>=sizeof(qint64)*2) && (myFileNameSize!=0))
        {
            in>>myFileName;
            myRcveBytes+=myFileNameSize;
            myLocPathFile->open(QFile::WriteOnly);
            ui->rfileSizeLineEdit->setText(myFileName);
        }
        else{
            return;
        }
    }
    if(myRcveBytes<myTotalBytes)
    {
        myRcveBytes+=myCntSocket->bytesAvailable();
        myInputBlock=myCntSocket->readAll();
        myLocPathFile->write(myInputBlock);
        myInputBlock.resize(0);
    }
    ui->recvProgressBar->setMaximum(myTotalBytes);
    ui->recvProgressBar->setValue(myRcveBytes);
    double transpeed=myRcveBytes/usedTime;
    ui->rfileSizeLineEdit->setText(tr("%1").arg(myTotalBytes/(1024*1024)+"MB"));
    ui->recvSizeLineEdit->setText(tr("%1").arg(myRcveBytes/(1024*1024)+"MB"));
    ui->rateLabel->setText(tr("%1").arg(transpeed*1000/(1024*1024),0,'f',2)+"MB/秒");
    if(myRcveBytes==myTotalBytes)
    {
        myLocPathFile->close();
        myCntSocket->close();
        ui->rateLabel->setText("接收完毕！");
    }
}
void FileCntDlg::getLocPath(QString lpath)
{
    myLocPathFile=new QFile(lpath);
}
void FileCntDlg::getSrvAddr(QHostAddress saddr)
{
    mySrvAddr=saddr;
    createConnToSrv();
}
