#pragma once

#include <QtWidgets/QWidget>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qnetworkreply.h>
#include <qpushbutton.h>
#include <qmutex.h>
#include <qeventloop.h>
#include "DemoThread.h"
#include <qthread.h>
#include "EmitWidget.h"
//#include "ui_QDemo.h"

class QDemo : public EmitWidget
{
	Q_OBJECT

public:
	QDemo(EmitWidget *parent = Q_NULLPTR);
	~QDemo();


public slots:
	void slotBtnDemo();
	void headImgConnect();
	void slot_finish(QVariant demo);

private:
	//Ui::QDemoClass ui;
	QPushButton				*m_btnDemo;
	QNetworkAccessManager	*m_headImgNAM;
	QNetworkReply			*m_headImgReply;
	QNetworkRequest			m_headImgRequest;
	QStringList				m_urlList;
	QMutex					m_mutex;
	//QHash<int ,QPixmap>		m_pixList;
	QList<QPixmap>			m_pixList;
	QEventLoop				loop;
	DemoThread				*m_pworker;
	QThread					*m_pthread;
};
