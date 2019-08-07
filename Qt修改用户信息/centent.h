#ifndef CENTENT_H
#define CENTENT_H

#include <QDialog>
#include <QFrame>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "baseinfo.h"
#include "contact.h"
#include "detail.h"

class Centent : public QFrame
{
    Q_OBJECT

public:
    Centent(QWidget *parent = 0);
    ~Centent();
    QStackedWidget *stack;
    QPushButton *AmendBtn;
    QPushButton *CloseBtn;
    BaseInfo *baseInfo;
    Contact *contact;
    Detail *detail;
};

#endif // CENTENT_H
