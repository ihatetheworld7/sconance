#include "QDemo.h"
#include <qdebug.h>
#include <QFileDialog>

QDemo::QDemo(EmitWidget *parent)
	: EmitWidget(parent)
{
	//ui.setupUi(this);
	m_btnDemo = new QPushButton(QStringLiteral("开始"),this);
	m_btnDemo->show();
	connect(m_btnDemo, &QPushButton::clicked, this, &QDemo::slotBtnDemo);
	m_urlList.append("http://news.lyd.com.cn/pic/003/003/254/00300325482_ccd48bb0.jpg");
	m_urlList.append("http://news.lyd.com.cn/pic/003/003/250/00300325083_3266a3fc.jpg");
	m_urlList.append("http://news.lyd.com.cn/pic/003/003/248/00300324889_6c0f6560.jpg");
	m_urlList.append("http://news.lyd.com.cn/pic/003/003/244/00300324443_c3ae9977.png");
	m_pworker = new DemoThread();
	m_pthread = new QThread();
	m_pworker->moveToThread(m_pthread);
	qDebug() << "start,thread id = " << QThread::currentThreadId();

	connect(m_pthread, &QThread::finished, m_pworker, &QObject::deleteLater);
	connect(this, SIGNAL(sig_dowork(QVariant)), m_pworker, SLOT(slot_dowork(QVariant)));
	connect(m_pworker, SIGNAL(sig_finish(QVariant)), this, SLOT(slot_finish(QVariant)));
}

void QDemo::slotBtnDemo()
{
	m_pthread->start();
	QVariant urlList;
	urlList.setValue(m_urlList);
	emit sig_dowork(urlList);
	//int num = m_urlList.size();
	//for (int i =0 ;i< num;++i)
	//{
	//	QNetworkAccessManager *headImgNAM = new QNetworkAccessManager(this);
	//	headImgNAM->setProperty("image", (i+1));
	//	QUrl url(m_urlList.at(i));
	//	m_headImgRequest.setUrl(url);
	//	//m_headImgRequest.setRawHeader("token");
	//	QByteArray demo("Mozilla / 5.0 (Windows NT 10.0; WOW64; Trident / 7.0; rv:11.0) like Gecko");
	//	m_headImgRequest.setRawHeader("User-Agent", demo);
	//	m_headImgReply = headImgNAM->get(m_headImgRequest);
	//	//connect(headImgNAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(headImgConnect(QNetworkReply*)));
	//	//connect(m_headImgReply, SIGNAL(finished()), this, SLOT(headImgConnect()));
	//	connect(m_headImgReply, SIGNAL(finished()), &loop, SLOT(quit()));
	//	loop.exec();
	//	QByteArray bytes = m_headImgReply->readAll();
	//	QPixmap pix;
	//	pix.loadFromData(bytes);
	//	m_pixList.push_back(pix);
	//}
	//if (m_urlList.size() == m_pixList.size())
	//{

	//	for (int i = 0; i < 4; ++i)
	//	{
	//		QString fileName = QString("./image/%1.jpg").arg((i + 1));
	//		//QFile *file = createFile(QString::fromLocal8Bit("image"),QString::number(i));
	//		QFile file(fileName);
	//		bool is_delete = file.exists();
	//		if (is_delete)
	//		{
	//			QFile::remove(fileName.toLocal8Bit());
	//		}
	//		bool is_create = file.open(QFile::WriteOnly | QFile::Truncate);
	//		if (!is_create)
	//		{
	//			qDebug() << QStringLiteral("打开文件失败");
	//			return;
	//		}
	//		//QImage pimage = m_pixList.value(i+1).toImage();
	//		QImage pimage = m_pixList.at(i).toImage();
	//		qDebug() << "pimage" << pimage;
	//		pimage.save(fileName, "jpg");
	//		file.close();
	//	}
	//	m_pixList.clear();
	//}
}

void QDemo::headImgConnect()
{
	/*m_mutex.lock();
	QNetworkAccessManager *head = qobject_cast<QNetworkAccessManager *>(sender());
	int value = head->property("image").toInt();
	int error = reply->error();
	QByteArray bytes = reply->readAll();
	QPixmap pix;
	pix.loadFromData(bytes);
	m_pixList.insert(value,pix);
	reply->deleteLater();
	
	m_mutex.unlock();*/
	//QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	//int error = reply->error();
	//QByteArray bytes = reply->readAll();
	//QPixmap pix;
	//pix.loadFromData(bytes);
	//m_pixList.push_back(pix);

	//if (m_urlList.size() == m_pixList.size())
	//{
	//	
	//	for (int i=0;i<4;++i)
	//	{
	//		QString fileName = QString("./image/%1.jpg").arg((i+1));
	//		//QFile *file = createFile(QString::fromLocal8Bit("image"),QString::number(i));
	//		QFile file(fileName);
	//		bool is_delete = file.exists();
	//		if (is_delete)
	//		{
	//			QFile::remove(fileName.toLocal8Bit());
	//		}
	//		bool is_create = file.open(QFile::WriteOnly | QFile::Truncate);
	//		if (!is_create)
	//		{
	//			qDebug() << QStringLiteral("打开文件失败");
	//			return;
	//		}
	//		//QImage pimage = m_pixList.value(i+1).toImage();
	//		QImage pimage = m_pixList.at(i).toImage();
	//		qDebug() << "pimage" << pimage;
	//		pimage.save(fileName,"jpg");
	//		file.close();
	//	}
	//}
	//reply->deleteLater();
	//loop.exit();
}

void QDemo::slot_finish(QVariant demo)
{
	qDebug() << "finish,thread id = " << QThread::currentThreadId();
	m_pixList.clear();
	m_pixList = demo.value<QList<QPixmap>>();
	if (m_urlList.size() == m_pixList.size())
	{

		for (int i = 0; i < 4; ++i)
		{
			QString fileName = QString("./image/%1.jpg").arg((i + 1));
			//QFile *file = createFile(QString::fromLocal8Bit("image"),QString::number(i));
			QFile file(fileName);
			bool is_delete = file.exists();
			if (is_delete)
			{
				QFile::remove(fileName.toLocal8Bit());
			}
			bool is_create = file.open(QFile::WriteOnly | QFile::Truncate);
			if (!is_create)
			{
				qDebug() << QStringLiteral("打开文件失败");
				return;
			}
			//QImage pimage = m_pixList.value(i+1).toImage();
			QImage pimage = m_pixList.at(i).toImage();
			qDebug() << "pimage" << pimage;
			pimage.save(fileName, "jpg");
			file.close();
		}
		m_pixList.clear();
	}
}

QDemo::~QDemo()
{
	qDebug() << "~QDemo()";
	m_pthread->quit();
	m_pthread->wait();
}

