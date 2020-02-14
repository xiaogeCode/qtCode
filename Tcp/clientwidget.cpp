#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}
