#ifndef OPENCV_1_H
#define OPENCV_1_H

#include <QWidget>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <QImage>
#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>
#include <QGridLayout>
using namespace cv;

class OPencv_1 : public QWidget
{
    Q_OBJECT

public:
    OPencv_1(QWidget *parent = nullptr);
    ~OPencv_1();

    void initMainWindow();
    void imgProc(float contrast, int brightness);

private slots:
    void slotContrastMoved(int position);
    void slotContrastChanged(int value);
    void slotBrightnessMoved(int position);
    void slotBrightnessChanged(int value);
private:
    Mat         myImg;
    QImage      myQImg;
    QLabel      *_viewLabel=nullptr;
    QHBoxLayout *_mainLayout = nullptr;
    QLabel      *_contrastLabel = nullptr;
    QLabel      *_brightnessLabel = nullptr;
    QSlider     *_contrastSlider = nullptr;
    QSlider     *_brightnessSlider = nullptr;
    QGridLayout *_GLayout = nullptr;

};

#endif // OPENCV_1_H
