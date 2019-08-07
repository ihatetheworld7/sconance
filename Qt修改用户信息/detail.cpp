#include "detail.h"

Detail::Detail(QWidget *parent) : QWidget(parent)
{
    m_nationalLabel=new QLabel("国家/地址：");
    m_nationalComboBox=new QComboBox;
    m_nationalComboBox->insertItem(0,("中国"));
    m_nationalComboBox->insertItem(1,("美国"));
    m_nationalComboBox->insertItem(2,("英国"));
    m_provinceLabel=new QLabel("省份：");
    m_provinceComboBox=new QComboBox;
    m_provinceComboBox->insertItem(0,("江苏省"));
    m_provinceComboBox->insertItem(1,("山东省"));
    m_provinceComboBox->insertItem(2,("浙江省"));
    m_cityLabel=new QLabel("城市：");
    m_cityLineEdit=new QLineEdit;
    m_introductLabel=new QLabel("个人说明：");
    m_introductTextEdit=new QTextEdit;
    m_mainLayout=new QGridLayout(this);
    m_mainLayout->setMargin(15);
    m_mainLayout->setSpacing(10);
    m_mainLayout->addWidget(m_nationalLabel,0,0);
    m_mainLayout->addWidget(m_nationalComboBox,0,1);
    m_mainLayout->addWidget(m_provinceLabel,1,0);
    m_mainLayout->addWidget(m_provinceComboBox,1,1);
    m_mainLayout->addWidget(m_cityLabel,2,0);
    m_mainLayout->addWidget(m_cityLineEdit,2,1);
    m_mainLayout->addWidget(m_introductLabel,3,0);
    m_mainLayout->addWidget(m_introductTextEdit,3,1);
}
