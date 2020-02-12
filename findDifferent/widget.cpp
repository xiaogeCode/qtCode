#include "widget.h"
#include "ui_widget.h"
#include "qpainter.h"
#include <QMouseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("魔方墙");

    //生成随机数种子
    qsrand(time(NULL));
    this->horizon = 2;
    this->verizon = 2;
    initGame();

    this->setGeometry(600,100,GAME_WIDTH,GAME_HEIGHT);
    ui->pushButton_tip->setGeometry(20,GAME_HEIGHT*2/3,40,50);
    ui->pushButton_Reset->setGeometry(100,GAME_HEIGHT*2/3,40,50);
    ui->label_show->setGeometry(GAME_WIDTH/2,GAME_HEIGHT*62/120,200,60);
    ui->label_show->setText(QString::number(horizon)+"X"+QString::number(verizon));


}
void Widget::initGame(){
    this->rectWidth = GAME_WIDTH/(horizon*2);
    this->rectHeight = GAME_HEIGHT/(verizon*2);
    createListData(horizon,verizon);
    isShowTips = false;
}
void Widget::paintEvent(QPaintEvent *event){
    QPainter p(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);


    for (int i = 0; i < horizon; ++i) {
        for (int j = 0; j < verizon; ++j) {
            int r = origionRgbList.at(i*verizon+j).R;
            int g = origionRgbList.at(i*verizon+j).G;
            int b = origionRgbList.at(i*verizon+j).B;
            brush.setColor(QColor(qRgb(r,g,b)));
            p.setBrush(brush);
            p.drawRect(i*rectWidth,j*rectHeight,rectWidth,rectHeight);
        }
    }
    for (int i = 0; i < horizon; ++i) {
        for (int j = 0; j < verizon; ++j) {
            int r = changedRgbList.at(i*verizon+j).R;
            int g = changedRgbList.at(i*verizon+j).G;
            int b = changedRgbList.at(i*verizon+j).B;
            brush.setColor(QColor(qRgb(r,g,b)));
            p.setBrush(brush);
            p.drawRect((i+horizon)*rectWidth,j*rectHeight,rectWidth,rectHeight);
        }
    }
    QPen pen;
    pen.setColor(Qt::red);
    p.setPen(pen);
    //竖直划线
    p.drawLine(rectWidth*horizon,0,rectWidth*horizon,rectHeight*verizon);

    //展示提示
    //isShowTips = true;
    if(isShowTips){
        brush.setStyle(Qt::NoBrush);
        p.setBrush(brush);
        int x = changedIndex/verizon;
        int y = changedIndex%verizon;

        p.drawEllipse(x*rectWidth,y*rectHeight,rectWidth,rectHeight);
        p.drawEllipse((x+horizon)*rectWidth,y*rectHeight,rectWidth,rectHeight);
    }


}
void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPoint p = event->globalPos()-this->frameGeometry().topLeft();
        int x = p.rx();
        //减去标题栏高度
        int titleHeight = frameGeometry().height() - geometry().height();
        int y = p.ry()-titleHeight;
        int x_n=x/rectWidth;
        int y_n=y/rectHeight;
        qDebug("x,y %d %d",x_n,y_n);
        qDebug("changedId %d",changedIndex);
        if((x_n*verizon+y_n == changedIndex)||((x_n-horizon)*verizon+y_n==changedIndex)){
            qDebug("well done");
            static int count=0;
            count++;
            if(count%4 == 0){
                this->horizon+=1;
                this->verizon+=1;
                count = 0;
            }

            //更新地图
            initGame();
            ui->label_show->setText(QString::number(horizon)+"X"+QString::number(verizon));
            update();
        }
    }
}
RgbValue Widget::randomRgb(){
    int r = qrand()%256;
    int g = qrand()%256;
    int b = qrand()%256;
    return RgbValue(r,g,b);
}
void Widget::createListData(int w, int h){
    //清空数据
    if(origionRgbList.size()>0){
        origionRgbList.clear();
    }
    if(changedRgbList.size()>0){
        changedRgbList.clear();
    }
    int size = w*h;
    //生产数据
    for (int i = 0; i < size; ++i) {
        RgbValue rgb = randomRgb();
        origionRgbList.append(rgb);
        changedRgbList.append(rgb);
    }
    //对1个数据进行变化
    changedIndex = qrand()%size;
    changedRgbList.replace(changedIndex,randomRgb());

}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_Reset_clicked()
{
    this->horizon=2;
    this->verizon=2;
    initGame();
    update();
}

void Widget::on_pushButton_tip_clicked()
{
    isShowTips = true;
    update();
}
