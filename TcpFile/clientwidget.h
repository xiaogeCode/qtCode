#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_pushButtonConnect_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpSocket;

    //文件对象
    QFile file;
    QString fileName;
    qint64 fileSize;
    //已经接收文件的大小
    qint64 recvSize;

    bool isStart;

};

#endif // CLIENTWIDGET_H
