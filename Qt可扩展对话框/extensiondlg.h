#ifndef EXTENSIONDLG_H
#define EXTENSIONDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

class ExtensionDlg : public QDialog
{
    Q_OBJECT

public:
    ExtensionDlg(QWidget *parent = 0);
    ~ExtensionDlg();
private:
    void createBaseInfo();
    void createDetailInfo();
    QWidget *baseWidget;
    QWidget *detailWidget;
};

#endif // EXTENSIONDLG_H
