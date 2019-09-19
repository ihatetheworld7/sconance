#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QtGui>
#include <QLabel>
#include <QStatusBar>

class mouseEvent : public QWidget
{
    Q_OBJECT

public:
    mouseEvent(QWidget *parent = 0);
    ~mouseEvent();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QLabel* statusLabel;
    QLabel* mousePosLabel;
    QStatusBar* statusBar;

};

#endif // MOUSEEVENT_H
