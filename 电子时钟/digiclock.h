#ifndef DIGICLOCK_H
#define DIGICLOCK_H
#include <QLCDNumber>
#include <QMouseEvent>
#include <QPalette>

class DigiClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigiClock();
    void mousePressEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void showTime();
private:
    QPoint m_startPoint;
    QPoint m_windowPoint;
    bool showColon;     //用于显示时间时是否显示：
    bool m_move;
};

#endif // DIGICLOCK_H
