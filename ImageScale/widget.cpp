#include "widget.h"
#include "ui_widget.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QStyleOption>
#include <QPainter>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint pos = event->pos();
    pos = this->mapToGlobal(pos);
    QMenu *menu = new QMenu(this);

    QAction *loadImage = new QAction(QString::fromLocal8Bit("Load Image"));
    connect(loadImage,&QAction::triggered,this,&Widget::onLoadImage);
    menu->addAction(loadImage);
    menu->addSeparator();

    QAction *zoomInAction = new QAction(QString::fromLocal8Bit("Zoom in"));
    connect(zoomInAction,&QAction::triggered,this,&Widget::onZoomInImage);
    menu->addAction(zoomInAction);

    QAction *zoomoutAction = new QAction(QString::fromLocal8Bit("Zoom out"));
    connect(zoomoutAction,&QAction::triggered,this,&Widget::onZoomOutImage);
    menu->addAction(zoomoutAction);

    QAction *presetAction = new QAction(QString::fromLocal8Bit("Preset"));
    connect(presetAction,&QAction::triggered,this,&Widget::onPresetImage);
    menu->addAction(presetAction);

    menu->exec(pos);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    if(m_Image.isNull())
        return QWidget::paintEvent(event);
    int width = qMin(m_Image.width(),this->width());
    int height = width*1.0/(m_Image.width()*1.0/m_Image.height());
    height = qMin(height,this->height());
    width = height*1.0*(m_Image.width()*1.0/m_Image.height());

    painter.translate(this->width() / 2 + m_XPtInterval, this->height() / 2 + m_YPtInterval);

    // 缩放
    painter.scale(m_ZoomValue, m_ZoomValue);

    QRect picRect(-width/2,-height/2,width,height);
    painter.drawImage(picRect,m_Image);
}

void Widget::wheelEvent(QWheelEvent *event)
{
    int value = event->delta();
    if(value>0)
        onZoomInImage();
    else {
        onZoomOutImage();
    }
    this->update();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_OldPos = event->pos();
    m_Pressed = true;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_Pressed)
            return QWidget::mouseMoveEvent(event);

        this->setCursor(Qt::SizeAllCursor);
        QPoint pos = event->pos();
        int xPtInterval = pos.x() - m_OldPos.x();
        int yPtInterval = pos.y() - m_OldPos.y();

        m_XPtInterval += xPtInterval;
        m_YPtInterval += yPtInterval;

        m_OldPos = pos;
        this->update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressed = false;
    this->setCursor(Qt::ArrowCursor);
}

void Widget::onLoadImage()
{
    QString imageFile = QFileDialog::getOpenFileName(this, "Open Image", "./", tr("Images (*.png *.xpm *.jpg)"));

    QFile file(imageFile);
    if(!file.exists())
        return;
    m_Image.load(imageFile);
}

void Widget::onZoomInImage()
{
    m_ZoomValue += 0.2;
    this->update();
}

void Widget::onZoomOutImage()
{
    m_ZoomValue -= 0.2;
    if (m_ZoomValue <= 0)
    {
        m_ZoomValue += 0.2;
        return;
    }

    this->update();
}

void Widget::onPresetImage()
{
    m_ZoomValue = 1.0;
    m_XPtInterval = 0;
    m_YPtInterval = 0;
    this->update();
}
