#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

class QNetworkReply;
class QNetworkAccessManager;
class QFile;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRequest(QUrl url);
private:
    Ui::MainWindow *ui;
private:
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QUrl url;
    QFile *file;
private slots:
    void replyFinished(QNetworkReply*);
    void httpFinished();
    void httpReadyRead();
    void updateData(qint64,qint64);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
