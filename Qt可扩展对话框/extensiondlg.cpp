#include "extensiondlg.h"

ExtensionDlg::ExtensionDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Extension Dialog");
    createBaseInfo();
    createDetailInfo();
    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(10);
}

ExtensionDlg::~ExtensionDlg()
{

}

void ExtensionDlg::createBaseInfo()
{
    baseWidget=new QWidget;
    QLabel *nameLabel=new QLabel("姓名：");
    QLineEdit *nameLineEdit=new QLineEdit;
    QLabel *sexLabel=new QLabel("性别：");
    QComboBox *sexComboBox=new QComboBox;
    sexComboBox->insertItem(0,("女"));
    sexComboBox->insertItem(1,("男"));
    QGridLayout *leftLayout=new QGridLayout;
    leftLayout->addWidget(nameLabel,0,0);
    leftLayout->addWidget(nameLineEdit,0,1);
    leftLayout->addWidget(sexLabel);
    leftLayout->addWidget(sexComboBox);
    QPushButton *okBtn=new QPushButton("确定");
    QPushButton *cancel=new QPushButton("详细");
    QDialogButtonBox *btnBox=new QDialogButtonBox(Qt::Vertical);
    btnBox->addButton(okBtn,QDialogButtonBox::ActionRole);
    btnBox->addButton(cancel,QDialogButtonBox::ActionRole);
    QHBoxLayout *mainLayouy=new QHBoxLayout(baseWidget);
    mainLayouy->addLayout(leftLayout);
    mainLayouy->addWidget(btnBox);
    connect(cancel,&QPushButton::clicked,[=](){
       if(detailWidget->isHidden())
           detailWidget->show();
       else
           detailWidget->hide();
    });
}

void ExtensionDlg::createDetailInfo()
{
    detailWidget=new QWidget;
    QLabel *ageLabel=new QLabel("年龄：");
    QLineEdit *ageLineEdit=new QLineEdit;
    ageLineEdit->setText("20");
    QLabel *departmentLabel=new QLabel("部门：");
    QComboBox *deparmentCombox=new QComboBox;
    deparmentCombox->addItem("部门1");
    deparmentCombox->addItem("部门2");
    deparmentCombox->addItem("部门3");
    deparmentCombox->addItem("部门4");
    QLabel *emailLabel=new QLabel("电子邮件：");
    QLineEdit *emailLineEdit=new QLineEdit;
    QGridLayout *mainLayout=new QGridLayout(detailWidget);
    mainLayout->addWidget(ageLabel,0,0);
    mainLayout->addWidget(ageLineEdit,0,1);
    mainLayout->addWidget(departmentLabel,1,0);
    mainLayout->addWidget(deparmentCombox,1,1);
    mainLayout->addWidget(emailLabel,2,0);
    mainLayout->addWidget(emailLineEdit,2,1);
    detailWidget->hide();

}
