#include "mouseevent.h"

mouseEvent::mouseEvent(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("鼠标事件");
    statusLabel=new QLabel;
    statusLabel->setText("当前位置：");
    statusLabel->setFixedWidth(100);
    mousePosLabel=new QLabel;
    mousePosLabel->setText("");
    mousePosLabel->setFixedWidth(100);
    statusBar=new QStatusBar;
    statusBar->addPermanentWidget(statusLabel);
    statusBar->addPermanentWidget(mousePosLabel);
    statusBar->show();
    this->setMouseTracking(true);
    resize(400,400);
}

mouseEvent::~mouseEvent()
{

}
void mouseEvent::mousePressEvent(QMouseEvent *event)
{
    QString str="("+QString::number(event->x())+","+QString::number(event->y())+")";
    if(event->button()==Qt::LeftButton)
        statusBar->showMessage("左键："+str);
    else if(event->button()==Qt::RightButton)
        statusBar->showMessage("右键："+str);
    else if(event->button()==Qt::MidButton)
        statusBar->showMessage("中间："+str);
}
void mouseEvent::mouseReleaseEvent(QMouseEvent *event)
{
    QString str="("+QString::number(event->x())+","+QString::number(event->y())+")";
    statusBar->showMessage("释放在："+str,3000);
}
void mouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    mousePosLabel->setText("("+QString::number(event->x())+","+QString::number(event->y())+")");
}
