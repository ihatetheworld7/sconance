#ifndef BASEINFO_H
#define BASEINFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class BaseInfo : public QWidget
{
    Q_OBJECT
public:
    explicit BaseInfo(QWidget *parent = nullptr);
private:
    QLabel *m_userNameLabel;
    QLabel *m_nameLabel;
    QLabel *m_sexLabel;
    QLabel *m_departmentLabel;
    QLabel *m_ageLabel;
    QLabel *m_otherLabel;
    QLineEdit *m_usernameLineEdit;
    QLineEdit *m_nameLineEdit;
    QComboBox *m_sexComboBox;
    QTextEdit *m_departmetTextEdit;
    QLineEdit *m_ageLineEdit;
    QGridLayout *m_leftLayout;

    QLabel *m_headLabel;
    QLabel *m_headIconLabel;
    QPushButton *m_updateBtn;
    QHBoxLayout *m_topRightLayout;
    QLabel *m_introductionLabel;
    QTextEdit *m_introductionTextEdit;
    QVBoxLayout *m_rightLayout;

signals:

public slots:
};

#endif // BASEINFO_H
