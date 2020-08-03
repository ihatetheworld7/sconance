#pragma once

#include <QObject>
#include <qthread.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qnetworkreply.h>
#include <QEventLoop>
#include <qvariant.h>
#include <qlist.h>

class DemoThread : public QObject
{
	Q_OBJECT

public:
	DemoThread(QObject *parent = nullptr);
	~DemoThread();

signals:
	void sig_finish(QVariant demo);

public slots:
	void slot_dowork(QVariant urlList);

private:
	QNetworkAccessManager	*m_headImgNAM;
	QNetworkReply			*m_headImgReply;
	QNetworkRequest			m_headImgRequest;
	QList<QPixmap>			m_pix;
	QVariant				DEMO;
	QStringList				m_urlList;
};
