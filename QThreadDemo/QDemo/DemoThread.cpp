#include "DemoThread.h"
#include <qdebug.h>
#include <QPixmap>

DemoThread::DemoThread(QObject *parent)
	: QObject(parent)
{
	qDebug() << "worker()";
	//qRegisterMetaType<QList<QPixmap>>("m_pix");
}

void DemoThread::slot_dowork(QVariant urlList)
{
	qDebug() << "do work,thread id = " << QThread::currentThreadId();
	m_urlList = urlList.value<QStringList>();
	int num = m_urlList.size();
	for (int i =0 ;i< num;++i)
	{
		QNetworkAccessManager *headImgNAM = new QNetworkAccessManager(this);
		headImgNAM->setProperty("image", (i+1));
		QUrl url(m_urlList.at(i));
		m_headImgRequest.setUrl(url);
		//m_headImgRequest.setRawHeader("token");
		QByteArray demo("Mozilla / 5.0 (Windows NT 10.0; WOW64; Trident / 7.0; rv:11.0) like Gecko");
		m_headImgRequest.setRawHeader("User-Agent", demo);
		m_headImgReply = headImgNAM->get(m_headImgRequest);
		QEventLoop	loop;
		//connect(headImgNAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(headImgConnect(QNetworkReply*)));
		//connect(m_headImgReply, SIGNAL(finished()), this, SLOT(headImgConnect()));
		connect(m_headImgReply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();
		QByteArray bytes = m_headImgReply->readAll();
		QPixmap pix;
		pix.loadFromData(bytes);
		m_pix.push_back(pix);
	}
	DEMO.setValue(m_pix);
	emit sig_finish(DEMO);
}

DemoThread::~DemoThread()
{
	qDebug() << "~worker()";
}
