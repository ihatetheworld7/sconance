#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void onLoadImage(void);
    void onZoomInImage(void);
    void onZoomOutImage(void);
    void onPresetImage(void);
private:
    Ui::Widget *ui;

    QImage m_Image;
    qreal m_ZoomValue = 1.0;
    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    QPoint m_OldPos;
    bool m_Pressed = false;
};
#endif // WIDGET_H
