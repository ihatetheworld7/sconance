#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFont>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QFont font;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
