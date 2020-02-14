#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    tcpSocker = NULL;
    //指定父对象，让其自动回收空间
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器 端口：8888");
    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
    {
        //取出建立好链接的套接字
        tcpSocker = tcpServer->nextPendingConnection();
        //获取对方IP和端口
        QString ip = tcpSocker->peerAddress().toString();
        qint16 port =tcpSocker->peerPort();
        QString tmp=QString("[%1:%2]:成功连接").arg(ip).arg(port);
        ui->textEditRead->setText(tmp);

        connect(tcpSocker,&QTcpSocket::readyRead,
                [=]()
        {
            //从通信套接字中取内容
            QByteArray array= tcpSocker->readAll();
            ui->textEditRead->append(array);
        }
        );
    }
    );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_pushButtonSend_clicked()
{
    if(tcpSocker == NULL){
        return;
    }
    //获取编辑区内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送数据
    tcpSocker->write(str.toUtf8().data());
}

void ServerWidget::on_pushButtonClose_clicked()
{
    if(tcpSocker == NULL){
        return;
    }
    //主动和客户端断开连接
    tcpSocker->disconnectFromHost();
    tcpSocker->close();
    tcpSocker = NULL;
}
