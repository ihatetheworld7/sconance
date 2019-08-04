#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void createCtrlFrame();
    void createContentFrame();
    void fillColorList(QComboBox*);
//private slots:
//    void ShowButton();
private:
    QFrame *m_ctrlFrame;
    QLabel *m_windowLabel;
    QComboBox *m_windowComboBox;
    QLabel *m_windowTextLabel;
    QComboBox *m_windowTextComboBox;
    QLabel *m_buttonLabel;
    QComboBox *m_buttonComboBox;
    QLabel *m_buttonTextLabel;
    QComboBox *m_buttonTextComboBox;
    QLabel *m_baseLabel;
    QComboBox *m_baseComboBox;
    QFrame *m_cententFrame;
    QLabel *m_label1;
    QComboBox *m_comboBox1;
    QLabel *m_label2;
    QComboBox *m_comboBox2;
    QLineEdit *m_lineEdit2;
    QTextEdit *m_textEdit;
    QPushButton *m_okBtn;
    QPushButton *m_cancle;
};

#endif // DIALOG_H
