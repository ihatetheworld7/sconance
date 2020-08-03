#pragma once

#include <QWidget>
#include <QVariant>

class EmitWidget : public QWidget
{
	Q_OBJECT

signals:
	void sig_dowork(QVariant urlList);
public:
	EmitWidget(QWidget *parent = nullptr);
	~EmitWidget();
};
