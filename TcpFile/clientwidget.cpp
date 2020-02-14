#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QMessageBox>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    isStart = true;

    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray buf = tcpSocket->readAll();
        //取出接收的内容
        if(true==isStart){
            //接收头
            isStart = false;
            //解析头部信息 文件名##文件大小 //初始化
            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();
            recvSize = 0;
            //打开文件
            file.setFileName(fileName);
            bool isOk = file.open(QIODevice::WriteOnly);
            if(false==isOk){
                qDebug("写文件打开失败");
            }
        }
        else{
            //文件信息
            qint64 len = file.write(buf);
            recvSize += len;

            if(recvSize == fileSize){
                file.close();
                tcpSocket->write("客户端接收完毕");
                QMessageBox::information(this,"完成","文件接收完成");

                tcpSocket->write("客户端接收完毕");
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
            }
        }
    }
    );
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButtonConnect_clicked()
{
    //获取服务器的ip 和端口
    QString ip = ui->lineEditIP->text();
    quint16 port= ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip),port);

}
