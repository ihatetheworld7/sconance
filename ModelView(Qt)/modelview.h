#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QMainWindow>

namespace Ui {
class ModelView;
}

class ModelView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModelView(QWidget *parent = 0);
    ~ModelView();

private:
    Ui::ModelView *ui;
};

#endif // MODELVIEW_H
