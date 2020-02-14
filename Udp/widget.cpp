#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("服务器端口为 8888");
    udpSocket = NULL;
    //分配空间，指定父对象
    udpSocket = new QUdpSocket(this);

}
void Widget::dealMsg(){
    //获取对方发送的内容
    char buf[1024]={0};
    //对方地址
    QHostAddress hostAddr;
    //对方端口
    quint16 port;
    qint64 len = udpSocket->readDatagram(buf,sizeof(buf),&hostAddr,&port);
    if(len>0){
        //格式化
        QString str= QString("[%1:%2]  %3")
                .arg(hostAddr.toString())
                .arg(port)
                .arg(buf);
        ui->textEditRead->setText(str);
    }

}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButtonSend_clicked()
{
    //先获取对方的IP和端口
    QString ip = ui->lineEditIP->text();
    qint16 port=ui->lineEditPort->text().toInt();

    QString str=ui->textEditWrite->toPlainText();
    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
}

void Widget::on_pushButtonBind_clicked()
{
    qint16 port=ui->lineEditSelfPort->text().toInt();
    setWindowTitle(QString("服务器端口为 %1").arg(ui->lineEditSelfPort->text()));
    //绑定
    udpSocket->bind(port);
/*
 * qq群原理
    udpSocket->bind(QHostAddress::AnyIPv6,port);
    //加入某个组播
    //组播地址是D类地址
    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.2"));
*/
    //当对方成功发送数据过来，自动触发readyRead();
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::dealMsg);
//    connect(udpSocket,&QUdpSocket::readyRead,
//            []()
//    {

//    }
//    );
}
