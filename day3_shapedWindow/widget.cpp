#include "widget.h"
#include "ui_widget.h"
#include <qpainter.h>
#include <QMouseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //窗口去边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //窗口背景透明
    setAttribute(Qt::WA_TranslucentBackground);

}
void Widget::paintEvent(QPaintEvent *event){
    QPainter p(this);
    //QMovie *movie = new QMovie(":/new/prefix1/Image/boy.gif");
    p.drawPixmap(0,0,200,200,QPixmap(":/new/prefix1/Image/gaoda.png"));


}
void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        //右键关闭窗口
        close();
    }else if (event->button() == Qt::LeftButton) {
        //当前坐标-窗口左上角坐标
        p = event->globalPos()-this->frameGeometry().topLeft();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        move(event->globalPos()-p);
    }
}
Widget::~Widget()
{
    delete ui;
}

