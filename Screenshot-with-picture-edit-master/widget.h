#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "screen.h"

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
    //void mousePressEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    Screen     *screen;
};

#endif // WIDGET_H
