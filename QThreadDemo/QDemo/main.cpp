#include "QDemo.h"
#include <QtWidgets/QApplication>
#include "标头.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//注册MessageHandler

	//qInstallMessageHandler(outputMessage);

	//打印日志到文件中

	/*qDebug("This is a debug message");

	qWarning("This is a warning message");

	qCritical("This is a critical message");*/

	//qFatal("This is a fatal message");
	//qint64 c;
	//qDebug() << "sizeof(c)" << sizeof(c);
	QDemo w;
	w.show();
	return a.exec();
}
