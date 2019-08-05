#include "digiclock.h"
#include <QTime>
#include <QTimer>
#include <QDebug>

DigiClock::DigiClock()
{
    m_move=false;
    QPalette p=palette();
    p.setColor(QPalette::Window,Qt::blue);
    setPalette(p);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.5);
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        QTime time=QTime::currentTime();
        QString text=time.toString("hh:mm");
        if(showColon)
        {
            text[2]=':';
            showColon=false;
        }
        else
        {
            text[2]=' ';
            showColon=true;
        }
        display(text);
    });
    timer->start(1000);
    showTime();
    resize(150,60);
    showColon=true;
}
void DigiClock::showTime()
{
    QTime time=QTime::currentTime();
    QString text=time.toString("hh:mm");
    if(showColon)
    {
        text[2]=':';
        showColon=false;
    }
    else
    {
        text[2]=' ';
        showColon=true;
    }
    display(text);
}
void DigiClock::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_move = true;
        m_startPoint = event->globalPos();
                //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
    if(event->button()==Qt::RightButton)
    {
        close();
    }
}
void DigiClock::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
         //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
        qDebug()<<"success";
//        move(event->globalPos()-dragPosition);
        event->accept();
    }
}
//void DigiClock::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton)
//       {
//           //改变移动状态.
//           m_move = false;
//       }
//}
