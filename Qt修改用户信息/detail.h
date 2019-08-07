#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

class Detail : public QWidget
{
    Q_OBJECT
public:
    explicit Detail(QWidget *parent = nullptr);
private:
    QLabel *m_nationalLabel;
    QComboBox *m_nationalComboBox;
    QLabel *m_provinceLabel;
    QComboBox *m_provinceComboBox;
    QLabel *m_cityLabel;
    QLineEdit *m_cityLineEdit;
    QLabel *m_introductLabel;
    QTextEdit *m_introductTextEdit;
    QGridLayout *m_mainLayout;

signals:

public slots:
};

#endif // DETAIL_H
