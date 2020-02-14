#ifndef SOCKETCLIENTWIDGET_H
#define SOCKETCLIENTWIDGET_H

#include <QWidget>
#include<QTcpSocket>

namespace Ui {
class SocketClientWidget;
}

class SocketClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SocketClientWidget(QWidget *parent = nullptr);
    ~SocketClientWidget();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::SocketClientWidget *ui;
    QTcpSocket *tcpSocket;
};

#endif // SOCKETCLIENTWIDGET_H
