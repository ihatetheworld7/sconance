#include "opencv_1.h"
#include <QDebug>

OPencv_1::OPencv_1(QWidget *parent)
    : QWidget(parent)
{   
    _mainLayout = new QHBoxLayout(this);
    _viewLabel = new QLabel(this);
    _viewLabel->setFixedSize(600,400);
    _mainLayout->addWidget(_viewLabel,9);
    _GLayout = new QGridLayout(this);
    _contrastSlider = new QSlider(this);
    _brightnessSlider = new QSlider(this);
    _contrastLabel = new QLabel(QString("contrast"),this);
    _brightnessLabel = new QLabel(QString("bright"),this);
    _GLayout->addWidget(_contrastSlider,0,0,9,1);
    _GLayout->addWidget(_brightnessSlider,0,1,9,1);
    _GLayout->addWidget(_contrastLabel,10,0,1,1);
    _GLayout->addWidget(_brightnessLabel,10,1,1,1);
    _mainLayout->addLayout(_GLayout,1);
    initMainWindow();
    connect(_contrastSlider,&QSlider::sliderMoved,this,&OPencv_1::slotContrastMoved);
    connect(_contrastSlider,&QSlider::valueChanged,this,&OPencv_1::slotContrastChanged);
    connect(_brightnessSlider,&QSlider::sliderMoved,this,&OPencv_1::slotBrightnessMoved);
    connect(_brightnessSlider,&QSlider::valueChanged,this,&OPencv_1::slotBrightnessChanged);
}

OPencv_1::~OPencv_1()
{

}

void OPencv_1::initMainWindow()
{
    QString imgFile("./demoImg.jpg");
    Mat imgData = imread(imgFile.toLatin1().data());
    //imshow("First show",imgData);
    cvtColor(imgData,imgData,COLOR_BGR2RGB);
    myImg = imgData;
    myQImg = QImage((const unsigned char*)imgData.data,imgData.cols,imgData.rows,QImage::Format_RGB888);
    _viewLabel->setPixmap(QPixmap::fromImage(myQImg.scaled(_viewLabel->size(),Qt::KeepAspectRatio)));
}

void OPencv_1::imgProc(float contrast, int brightness)
{
    Mat imgSrc = myImg;
    Mat imgDst = Mat::zeros(imgSrc.size(),imgSrc.type());
    imgSrc.convertTo(imgDst,-1,contrast,brightness);
    myQImg = QImage((const unsigned char *)imgDst.data,imgDst.cols,imgDst.rows,QImage::Format_RGB888);
    _viewLabel->setPixmap(QPixmap::fromImage(myQImg.scaled(_viewLabel->size(),Qt::KeepAspectRatio)));
}

void OPencv_1::slotContrastMoved(int position)
{
    imgProc(position/33.3,0);
}

void OPencv_1::slotContrastChanged(int value)
{
    imgProc(value/33.3,0);
}

void OPencv_1::slotBrightnessMoved(int position)
{
    imgProc(1.0,position);
}

void OPencv_1::slotBrightnessChanged(int value)
{
    imgProc(1.0,value);
}
