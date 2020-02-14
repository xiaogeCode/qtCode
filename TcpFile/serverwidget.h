#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

    //发送文件数据
    void sendData();

private slots:
    void on_pushButtonChooseFile_clicked();

    void on_pushButtonSendFile_clicked();

private:
    Ui::ServerWidget *ui;
    //监听套接字
    QTcpServer *tcpServer;
    //通信套接字
    QTcpSocket *tcpSocker;
    //文件对象
    QFile file;
    QString fileName;
    qint64 fileSize;
    //已经发送文件的大小
    qint64 sendSize;
    //定时器
    QTimer timer;
};
#endif // SERVERWIDGET_H
