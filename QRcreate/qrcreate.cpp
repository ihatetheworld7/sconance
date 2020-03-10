#include "qrcreate.h"
#include "ui_qrcreate.h"
#include <QImage>

QRcreate::QRcreate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRcreate)
{
    ui->setupUi(this);
}

QRcreate::~QRcreate()
{
    delete ui;
}

void QRcreate::Show_QRcode_Picture(QString message)
{
    std::vector<QrSegment> segs =
           QrSegment::makeSegments(message.toLatin1());
       QrCode qr1 = QrCode::encodeSegments(
           segs, QrCode::Ecc::HIGH, 5, 5, 2, false);
       //创建二维码画布
       QImage QrCode_Image=QImage(qr1.getSize(),qr1.getSize(),QImage::Format_RGB888);

       for (int y = 0; y < qr1.getSize(); y++) {
           for (int x = 0; x < qr1.getSize(); x++) {
               if(qr1.getModule(x, y)==0)
                   QrCode_Image.setPixel(x,y,qRgb(255,255,255));
               else
                   QrCode_Image.setPixel(x,y,qRgb(0,0,0));
           }
       }

       //图像大小转换为适当的大小
       QrCode_Image=QrCode_Image.scaled(ui->label->width(),ui->label->height(),
                       Qt::KeepAspectRatio);
       //转换为QPixmap在Label中显示
       ui->label->setPixmap(QPixmap::fromImage(QrCode_Image));
}

void QRcreate::on_pushButton_clicked()
{
    Show_QRcode_Picture(ui->textEdit->toPlainText());
}
