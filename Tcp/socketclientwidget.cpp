#include "socketclientwidget.h"
#include "ui_socketclientwidget.h"
#include <QHostAddress>

SocketClientWidget::SocketClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SocketClientWidget)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
    {
        //连接成功
        ui->textEditRead->setText("成功和服务器建立连接");
    }
    );
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
    {
        //获取对方内容
        QByteArray array=tcpSocket->readAll();
        this->ui->textEditRead->append(array);
    }
    );

}

SocketClientWidget::~SocketClientWidget()
{
    delete ui;
}

void SocketClientWidget::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);

}

void SocketClientWidget::on_pushButtonSend_clicked()
{
    //获取编辑框内容
    QString str=ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void SocketClientWidget::on_pushButtonClose_clicked()
{
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
