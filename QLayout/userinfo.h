#ifndef USERINFO_H
#define USERINFO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class UserInfo : public QDialog
{
    Q_OBJECT

public:
    UserInfo(QWidget *parent = 0);
    ~UserInfo();
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

    QPushButton *m_okBtn;
    QPushButton *m_cancelBtm;
    QHBoxLayout *m_bottomLayout;
};

#endif // USERINFO_H
