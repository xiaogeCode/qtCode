#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTimer>
ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器端口:8888");
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);
    //如果客户端和服务器成功连接，会自动触发newConnection
    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
    {
        //取出连接的套接字
        tcpSocker = tcpServer->nextPendingConnection();
        //获取对方IP和端口
        QString ip = tcpSocker->peerAddress().toString();
        quint16 port= tcpSocker->peerPort();
        QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
        this->ui->textEdit->setText(str);

        connect(tcpSocker,&QTcpSocket::readyRead,
                [=]()
        {
            QByteArray buf=tcpSocker->readAll();
            QString str = QString(buf);
            qDebug("buf");
            ui->textEdit->append(QString(buf));

            //把客户端断开
            tcpSocker->disconnectFromHost();
            tcpSocker->close();

        }
        );
    }
    );
    connect(&timer,&QTimer::timeout,
            [=]()
    {
        //关闭定时器
        timer.stop();
        //发送文件
        sendData();
    }
   );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//选择文件按钮
void ServerWidget::on_pushButtonChooseFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    //选择文件路径有效
    if(false == filePath.isEmpty()){
        fileName.clear();
        fileSize = 0;
        sendSize = 0;

        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();

        //只读方式打开
        file.setFileName(filePath);
        bool ok=file.open(QIODevice::ReadOnly);
        if(false == ok){
            qDebug("打开文件失败");
        }
        //添加提示
        ui->textEdit->append(filePath);


    }
    else{
        qDebug("选择文件路径出错");
    }
}
//发送文件按钮
void ServerWidget::on_pushButtonSendFile_clicked()
{
    //先发送文件头信息 文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 headLen= tcpSocker->write(head.toUtf8());
    //头部信息发送成功
    if(headLen>0){
        //发送真正的文件信息
        //防止tcp 粘包 通过定时延时20ms
        timer.start(20);

    }
    else{
        qDebug("头部信息发送失败");
        file.close();
    }
    // 在发送真正的文件信息

}
void ServerWidget::sendData(){
    qint64 len = 0;
    do{
        //每次发送数据的大小
        char buf[1024]= {0};
        //从文件中读数据
        len = file.read(buf,sizeof(buf));
        //读多少发多少
        tcpSocker->write(buf,len);
        //发送的数据需要累加
        sendSize += len;
    }while(len>0);
    //是否发送完毕
    if(sendSize==fileSize){
        ui->textEdit->append("文件发送完毕");
        file.close();

        //把客户端断开
//        tcpSocker->disconnectFromHost();
//        tcpSocker->close();
    }

}
