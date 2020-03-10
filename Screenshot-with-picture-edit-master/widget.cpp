#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->showMaximized();
    screen = new Screen(this);
    QSize size = this->maximumSize();
    screen->resize(size);
    connect(screen,&Screen::emitClose,this,&Widget::close);
}


Widget::~Widget()
{
    delete ui;
}

//void Widget::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button()==Qt::RightButton)
//        this->close();
//}
