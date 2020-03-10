#ifndef QRCREATE_H
#define QRCREATE_H

#include <QWidget>

#include <string>
#include <vector>
#include "QrCode.hpp"
using namespace qrcodegen;

namespace Ui {
class QRcreate;
}

class QRcreate : public QWidget
{
    Q_OBJECT

public:
    explicit QRcreate(QWidget *parent = 0);
    ~QRcreate();

    void Show_QRcode_Picture(QString message);

private slots:
    void on_pushButton_clicked();

private:
    Ui::QRcreate *ui;
};

#endif // QRCREATE_H
