#include "dialog.h"
#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(m_ctrlFrame);
    mainLayout->addWidget(m_cententFrame);

//    QPalette palette(this->palette());
//    palette.setColor(QPalette::Background, Qt::black);
//    this->setPalette(palette);
}

Dialog::~Dialog()
{

}

void Dialog::createCtrlFrame()
{   
    m_ctrlFrame=new QFrame;
    m_windowLabel=new QLabel("QPalette:window:");
    m_windowComboBox=new QComboBox;
    fillColorList(m_windowComboBox);
    connect(m_windowComboBox,static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),[=]()
    {
       QStringList colorList=QColor::colorNames();
       QColor color=QColor(colorList[m_windowComboBox->currentIndex()]);
       QPalette p=m_cententFrame->palette();
       p.setColor(QPalette::Window,color);
       m_cententFrame->setPalette(p);
       m_cententFrame->update();


    });
    m_windowTextLabel=new QLabel("QPalette::windowtext:");
    m_windowTextComboBox=new QComboBox;
    fillColorList(m_windowTextComboBox);
    connect(m_windowTextComboBox,static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),[=](){
       QStringList colorList=QColor::colorNames();
       QColor color=colorList[m_windowTextComboBox->currentIndex()];
       QPalette p=m_cententFrame->palette();
       p.setColor(QPalette::WindowText,color);
       m_cententFrame->setPalette(p);
    });
    m_buttonLabel= new QLabel("QPalette::Button:");
    m_buttonComboBox=new QComboBox;
    fillColorList(m_buttonComboBox);
    connect(m_buttonComboBox,static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),[=](){
       QStringList colorList=QColor::colorNames();
       QColor color=QColor(colorList[m_buttonComboBox->currentIndex()]);
       QPalette p=m_cententFrame->palette();
       p.setColor(QPalette::Button,color);
       m_cententFrame->setPalette(p);
       m_cententFrame->update();
    });
//    connect(m_buttonComboBox,SIGNAL(activated(int)),this,SLOT(ShowButton()));
    m_buttonTextLabel=new QLabel("QPalette::ButtonText:");
    m_buttonTextComboBox=new QComboBox;
    fillColorList(m_buttonTextComboBox);
    connect(m_buttonTextComboBox,static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),[=](){
        QStringList colorList=QColor::colorNames();
        QColor color=QColor(colorList[m_buttonTextComboBox->currentIndex()]);
        QPalette p=m_cententFrame->palette();
        p.setColor(QPalette::ButtonText,color);
        m_cententFrame->setPalette(p);
    });
    m_baseLabel=new QLabel("QPalette::Base:");
    m_baseComboBox=new QComboBox;
    fillColorList(m_baseComboBox);
    connect(m_baseComboBox,static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),[=](){
        QStringList colorList=QColor::colorNames();
        QColor color=QColor(colorList[m_baseComboBox->currentIndex()]);
        QPalette p=m_cententFrame->palette();
        p.setColor(QPalette::Base,color);
        m_cententFrame->setPalette(p);
    });
    QGridLayout *mainLayout=new QGridLayout(m_ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(m_windowLabel,0,0);
    mainLayout->addWidget(m_windowComboBox,0,1);
    mainLayout->addWidget(m_windowTextLabel,1,0);
    mainLayout->addWidget(m_windowTextComboBox,1,1);
    mainLayout->addWidget(m_buttonLabel,2,0);
    mainLayout->addWidget(m_buttonComboBox,2,1);
    mainLayout->addWidget(m_buttonTextLabel,3,0);
    mainLayout->addWidget(m_buttonTextComboBox,3,1);
    mainLayout->addWidget(m_baseLabel,4,0);
    mainLayout->addWidget(m_baseComboBox,4,1);
    
}
void Dialog::createContentFrame()
{
    m_cententFrame=new QFrame;
    m_label1=new QLabel("请选择一个值");
    m_comboBox1=new QComboBox;
    m_label2=new QLabel("请输入一个值");
    m_textEdit=new QTextEdit;
    m_lineEdit2=new QLineEdit;
    QGridLayout *TopLayout=new QGridLayout;
    TopLayout->addWidget(m_label1,0,0);
    TopLayout->addWidget(m_comboBox1,0,1);
    TopLayout->addWidget(m_label2,1,0);
    TopLayout->addWidget(m_lineEdit2,1,1);
    TopLayout->addWidget(m_textEdit,2,0,1,2);
    m_okBtn=new QPushButton("确认");
    m_cancle=new QPushButton("取消");
    QHBoxLayout *buttomLayout=new QHBoxLayout;
    buttomLayout->addStretch(1);
    buttomLayout->addWidget(m_okBtn);
    buttomLayout->addWidget(m_cancle);
    QVBoxLayout *mainLayout=new QVBoxLayout(m_cententFrame);
    mainLayout->addLayout(TopLayout);
    mainLayout->addLayout(buttomLayout);

}
void Dialog::fillColorList(QComboBox *comboBox)
{
    QStringList colorList=QColor::colorNames();
    QString color;
    foreach (color, colorList) {
       QPixmap pix(QSize(70,20));
       pix.fill(QColor(color));
       comboBox->addItem(QIcon(pix),NULL);
       comboBox->setIconSize(QSize(70,20));
       comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}
//void Dialog::ShowButton()
//{
//    QStringList colorList=QColor::colorNames();
//    QColor color=QColor(colorList[m_buttonComboBox->currentIndex()]);
//    QPalette p=m_cententFrame->palette();
//    p.setColor(QPalette::Button,color);
//    m_cententFrame->setPalette(p);
//}
