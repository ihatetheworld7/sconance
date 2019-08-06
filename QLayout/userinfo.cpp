#include "userinfo.h"
#include <QFrame>
#include <QPixmap>

UserInfo::UserInfo(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("UserInfo"));
    m_userNameLabel=new QLabel("用户名：");
    m_usernameLineEdit=new QLineEdit;
    m_nameLabel=new QLabel("姓名：");
    m_nameLineEdit=new QLineEdit;
    m_sexLabel=new QLabel("性别：");
    m_sexComboBox=new QComboBox;
    m_sexComboBox->addItem("女");
    m_sexComboBox->addItem("男");
    m_departmentLabel=new QLabel("部门：");
    m_departmetTextEdit=new QTextEdit;
    m_ageLabel=new QLabel("年龄：");
    m_ageLineEdit=new QLineEdit;
    m_otherLabel=new QLabel("备注：");
    m_otherLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_leftLayout=new QGridLayout();
    m_leftLayout->addWidget(m_userNameLabel,0,0);
    m_leftLayout->addWidget(m_usernameLineEdit,0,1);
    m_leftLayout->addWidget(m_nameLabel,1,0);
    m_leftLayout->addWidget(m_nameLineEdit,1,1);
    m_leftLayout->addWidget(m_sexLabel,2,0);
    m_leftLayout->addWidget(m_sexComboBox,2,1);
    m_leftLayout->addWidget(m_departmentLabel,3,0);
    m_leftLayout->addWidget(m_departmetTextEdit,3,1);
    m_leftLayout->addWidget(m_ageLabel,4,0);
    m_leftLayout->addWidget(m_ageLineEdit,4,1);
    m_leftLayout->addWidget(m_otherLabel,5,0,1,2);
    m_leftLayout->setColumnStretch(0,1);
    m_leftLayout->setColumnStretch(1,3);

    m_headLabel=new QLabel("头像：");
    m_headIconLabel=new QLabel;
    QPixmap icon("D:\\Image\\1.jpg");
    m_headIconLabel->setPixmap(icon);
    m_headIconLabel->resize(30,30);

    m_updateBtn=new QPushButton("更新");
    m_topRightLayout=new QHBoxLayout();
    m_topRightLayout->setSpacing(20);
    m_topRightLayout->addWidget(m_headLabel);
    m_topRightLayout->addWidget(m_headIconLabel);
    m_topRightLayout->addWidget(m_updateBtn);
    m_introductionLabel=new QLabel("个人说明：");
    m_introductionTextEdit=new QTextEdit;
    m_rightLayout=new QVBoxLayout();
    m_rightLayout->addLayout(m_topRightLayout);
    m_rightLayout->addWidget(m_introductionLabel);
    m_rightLayout->addWidget(m_introductionTextEdit);

    m_okBtn=new QPushButton("确认");
    m_cancelBtm=new QPushButton("取消");
    m_bottomLayout=new QHBoxLayout();
    m_bottomLayout->addStretch();
    m_bottomLayout->addWidget(m_okBtn);
    m_bottomLayout->addWidget(m_cancelBtm);

    QGridLayout *m_mainLayout=new QGridLayout(this);
    m_mainLayout->setMargin(15);
    m_mainLayout->setSpacing(10);
    m_mainLayout->addLayout(m_leftLayout,0,0);
    m_mainLayout->addLayout(m_rightLayout,0,1);
    m_mainLayout->addLayout(m_bottomLayout,1,0,1,2);
    m_mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

UserInfo::~UserInfo()
{

}
