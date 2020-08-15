#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
    //font.setFamily(QStringLiteral("Microsoft YaHei"));
}

void MyLabel::wrapData(const QString &text)
{
    QFontMetrics font(this->font());
        int nTextSize = font.width(text);
        int nLabelSize = this->width();
        if(nTextSize > nLabelSize){
            QString qstrData = SpliteText(font, text, nLabelSize);

            QLabel::setText(qstrData);
            return;
        }

        QLabel::setText(text);
}

QString MyLabel::SpliteText(const QFontMetrics &font, const QString &text, int nLabelSize)
{
    int nTextSize = font.width(text);
        if(nTextSize > nLabelSize){
            int nPos = 0;
            long nOffset = 0;
            for (int i = 0; i < text.size(); i++){
                nOffset += font.width(text.at(i));
                if(nOffset >= nLabelSize){
                    nPos = i;
                    break;
                }
            }

            nPos = (nPos -1 < 0) ? 0 : nPos -1;//zr.主要是为了防止截取字符串的位置是-1.回退一个字节的作用是换行,防止字符有一半显示一半未显示

            QString qstrLeftData = text.left(nPos);
            QString qstrMidData = text.mid(nPos);
            return qstrLeftData + "\n" + SpliteText(font, qstrMidData, nLabelSize);
        }
        return text;
}

MyLabel::~MyLabel()
{

}


