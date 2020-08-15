#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QFontMetrics>
#include <QFont>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent=nullptr);
    ~MyLabel();

    void wrapData(const QString& text);
private:
    QString SpliteText(const QFontMetrics& font, const QString& text, int nLabelSize);
private:
    //QFont   font;
};

#endif // MYLABEL_H
