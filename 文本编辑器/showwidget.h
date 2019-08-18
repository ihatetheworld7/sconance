#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QTextEdit>
#include <QHBoxLayout>

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);
    QImage img;
    QLabel *imageLabel;
    QTextEdit *text;
    

signals:

public slots:
};

#endif // SHOWWIDGET_H
