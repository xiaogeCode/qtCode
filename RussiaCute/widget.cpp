#include "widget.h"
#include "ui_widget.h"
#include <qdebug.h>
#include <qpainter.h>
#include <QKeyEvent>
#include <QTime>
#include <QElapsedTimer>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(600,100,(CUTE_LEN +1)*(GAME_WIDTH+3),(CUTE_LEN +1)*GAME_HEIGHT+10);
    this->setWindowTitle("俄罗斯方块");
    initGame();
    //生成随机数种子
    qsrand(time(NULL));

    timeId = startTimer(1000);
    isPause = false;


}
void Widget::initGame(){
    //清空地图
    for (int i = 0; i < GAME_WIDTH; ++i) {
        for (int j = 0; j < GAME_HEIGHT; ++j) {
            cuteListArray[i][j] = 0;
        }
    }
    //设置随机方块在位置，在最顶行正中央
    currentX =( GAME_WIDTH-4)/2;
    currentY = 0;
    //初始化下一个方块
    createRandomCute();
    //给当前在随机方块赋值
    memcpy(currentCuteArray,nextCuteArray,sizeof(nextCuteArray));
    currentCuteType = nextCuteType;
    //继续生产下一个随机方块
    createRandomCute();

    isQucikMove = false;

    //防止键盘时间被子控件捕获
    this->setFocus();

    ui->pushButton_rota->setGeometry((CUTE_LEN +1)*GAME_WIDTH+CUTE_LEN/2,(CUTE_LEN +1)*(GAME_HEIGHT-5),CUTE_LEN*2,30);
    ui->pushButton_left->setGeometry((CUTE_LEN +1)*GAME_WIDTH+CUTE_LEN/2,(CUTE_LEN +1)*(GAME_HEIGHT-4),CUTE_LEN,30);
    ui->pushButton_right->setGeometry((CUTE_LEN +1)*(GAME_WIDTH+1)+CUTE_LEN/2,(CUTE_LEN +1)*(GAME_HEIGHT-4),CUTE_LEN,30);
    ui->pushButton_qucikmove->setGeometry((CUTE_LEN +1)*(GAME_WIDTH+1),(CUTE_LEN +1)*(GAME_HEIGHT-3),CUTE_LEN,30);
    ui->pushButton_Reset->setGeometry((CUTE_LEN +1)*(GAME_WIDTH+1),(CUTE_LEN +1)*(GAME_HEIGHT-2),CUTE_LEN,30);
    ui->pushButton_pause->setGeometry((CUTE_LEN +1)*(GAME_WIDTH+1),(CUTE_LEN +1)*(GAME_HEIGHT-1),CUTE_LEN,30);


}
void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    //画地图
    QBrush brush;
    brush.setStyle(Qt::Dense1Pattern);
    brush.setColor(Qt::red);
    p.setBrush(brush);
    for (int i = 0; i < GAME_WIDTH; ++i) {
        for (int j = 0; j < GAME_HEIGHT; ++j) {
            if(cuteListArray[i][j] ==1){
                p.drawRect(i*(CUTE_LEN +1), j*(CUTE_LEN +1), CUTE_LEN, CUTE_LEN);
            }
        }
    }
    //画随机方块
    brush.setColor(Qt::blue);
    p.setBrush(brush);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(currentCuteArray[i][j] ==1){
                //p.drawRect(i*(CUTE_LEN +1), j*(CUTE_LEN +1), CUTE_LEN, CUTE_LEN);
                p.drawRect((i+ currentX)*(CUTE_LEN +1), (j+ currentY)*(CUTE_LEN +1), CUTE_LEN, CUTE_LEN);
            }
        }
    }
    //画下一个提示方块
    brush.setColor(Qt::green);
    p.setBrush(brush);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(nextCuteArray[i][j] ==1){
                //p.drawRect(i*(CUTE_LEN +1), j*(CUTE_LEN +1), CUTE_LEN, CUTE_LEN);
                p.drawRect((i+ GAME_WIDTH*2)*(CUTE_LEN/2 +1), (j+ 1)*(CUTE_LEN/2 +1), CUTE_LEN/2, CUTE_LEN/2);
            }
        }
    }

    //竖直划线
    p.drawLine((CUTE_LEN +1)*GAME_WIDTH,0,(CUTE_LEN +1)*GAME_WIDTH,(CUTE_LEN +1)*GAME_HEIGHT);
    //水平划线
    p.drawLine(0,(CUTE_LEN +1)*GAME_HEIGHT,(CUTE_LEN +1)*GAME_WIDTH,(CUTE_LEN +1)*GAME_HEIGHT);

}
void Widget::createRandomCute(){
    int n = qrand()%8+1;
    nextCuteType = n;
//    int tmp[4][4] = {{0, 0, 0, 0},{1, 1, 1, 1},{0, 0, 0, 0},{0, 0, 0, 0}};
//    memccpy(currentCuteArray,tmp,4,sizeof(tmp[0]));
//    qDebug("create");
    switch(n){
    case 1:{
        //1
        int tmp[4][4] = {{0, 0, 0, 0},{1, 1, 1, 1},{0, 0, 0, 0},{0, 0, 0, 0}};
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }
    case 2:{
        //
        int tmp[4][4] = {{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 0, 0}};
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }
    case 3:
    {
        //
        int tmp[4][4] ={ {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0 }};
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }
    case 4:{
        //
        int tmp[4][4] = {{ 1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} };
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }

    case 5:
    {
        //N
       int tmp[4][4] ={ {0, 1, 1, 0},{ 1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
       memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }
    case 6:{
        //N
        int tmp[4][4] ={{ 1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }};
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }
    case 7:
    {
        //T
        int tmp[4][4] ={{ 1, 0, 0, 0},{ 1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0 }};
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }
    case 8:{
        //
        int tmp[4][4] ={ {1, 1, 0, 0}, {1, 1, 0, 0},{ 0, 0, 0, 0}, {0, 0, 0, 0} };
        memcpy(nextCuteArray,tmp,sizeof(tmp));
        break;
    }

    default:
            break;
    }
//    qDebug("n : +%d",n);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
//            qDebug("%d",currentCuteArray[i][j]);
        }
    }

}
void Widget::timerEvent(QTimerEvent *){
    moveCute(2);
    update();

}
void Widget::keyReleaseEvent(QKeyEvent *event){
    qDebug("1111event");
    int key=event->key();
    switch (key) {
    //空格翻转
    case Qt::Key_Space:{
        qDebug("space");
        roteCute();
        update();
        break;
    }
    //重置游戏
    case Qt::Key_R:{
        initGame();
        update();
        break;
    }
    //左移动
    case Qt::Key_A:
    {
        qDebug("aaa event");
        moveCute(0);
        break;
    }
    //右移动
    case Qt::Key_D:{
        qDebug("ddd event");
        moveCute(1);
        break;
    }
    //快速移动
    case Qt::Key_S:{
        isQucikMove = true;
        qDebug("ssss event");

        //快速移动
        for (int i = 0; i < 20; ++i) {
            if(!isQucikMove){
                break;
            }
            moveCute(2);
        }
        break;
    }

    default:
        break;
    }
}
bool Widget::canCuteMove(int direction){
    int a[3]={-1,1,0};
    int b[3]={0,0,1};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(currentCuteArray[i][j]==1){
                int newX =i+a[direction]+this->currentX;
                int newY =j+b[direction]+this->currentY;

                if(newX<0 || newX>GAME_WIDTH -1 || newY<0 || newY>GAME_HEIGHT -1){
                    return false;
                }
                if(cuteListArray[newX][newY]==1){
                    return false;
                }
            }
        }
    }
    return true;
}
void Widget::moveCute(int direction){
    if(canCuteMove(direction)){
        //direction 0  1  2
        int a[3]={-1,1,0};
        int b[3]={0,0,1};
        this->currentX = this->currentX +a[direction];
        this->currentY = this->currentY +b[direction];

        if(isCuteToBotom()){
            if(!(canCuteMove(0) ||canCuteMove(1))){
                handleToCuteToBotom();
            }else{
                handleToCuteToBotom();


//                QTime dieTime = QTime::currentTime().addMSecs(300);
//                QTime dealTime = QTime::currentTime().addMSecs(250);

//                while( QTime::currentTime() < dieTime ){
//                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//                    if(QTime::currentTime()>dealTime){
//                        handleToCuteToBotom();
//                    }
//                }


//                cuteBotomtimer();
            }

        }
        update();
    }
}
bool Widget::isCuteToBotom(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(currentCuteArray[i][j]==1){
                int newX =i+this->currentX;
                int newY =j+1+this->currentY;
                //到达最低行
                if(j+this->currentY == GAME_HEIGHT -1){
                    return true;
                }
                //碰到已经存在的方块
                if(cuteListArray[newX][newY]==1){
                    return true;
                }
            }
        }
    }
    return false;
}
void Widget::handleToCuteToBotom(){
    //更新地图
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(currentCuteArray[i][j]==1){
                cuteListArray[i+ currentX][j+ currentY]=1;
            }
        }
    }
    //消除方块
    dismissCutes();

    isQucikMove = false;

    //设置随机方块在位置，在最顶行正中央
    currentX =( GAME_WIDTH-4)/2;
    currentY = 0;
    //重新生成随机方块
    //给当前在随机方块赋值
    memcpy(currentCuteArray,nextCuteArray,sizeof(nextCuteArray));
    currentCuteType = nextCuteType;

    //继续生产下一个随机方块
    createRandomCute();
}
void Widget::dismissCutes(){
//    qDebug("dismissCutes");
    for(int i = currentY; i< GAME_HEIGHT; i++){
        if(canCuteMiss(i)){
            dissmissCuteLine(i);
        }
    }
}
bool Widget::canCuteMiss(int row){
    if(row<0 || row> GAME_HEIGHT -1){
        return false;
    }
    for(int i = 0; i< GAME_WIDTH; i++){
        if(cuteListArray[i][row]==0){
            return false;
        }
    }
    return true;
}
void Widget::dissmissCuteLine(int row){
    if(row> GAME_HEIGHT -1){
        return;
    }
//    qDebug("dissmiss cuteline");
    for(int i = 0; i< GAME_WIDTH; i++){
//        System.arraycopy(cuteListArray[i], 0, cuteListArray[i], 1, row);
        for (int j = row; j >0; j--) {
            cuteListArray[i][j] = cuteListArray[i][j-1];
        }
    }
}
bool Widget::canCuteRote(){
    //田 方形不用旋转
    if(currentCuteType ==8){
        return false;
    }
    int switchLen = 3;
    // 一 字形
    if(currentCuteType ==1 || currentCuteType ==2){

        switchLen=4;
    }
    int roteArray[4][4] ={0};

    for(int i=0;i<switchLen;i++){
        for(int j=0;j<switchLen;j++){
            roteArray[i][j]= currentCuteArray[j][switchLen-1-i];
        }
    }
    for(int i1=0;i1<4;i1++){
        for(int j1=0;j1<4;j1++){
            if(roteArray[i1][j1]==1){
                int tmpX = i1+ currentX;
                int tmpY = j1+ currentY;
                if(tmpX<0 || tmpX> GAME_WIDTH -1 ||tmpY<0 || tmpY> GAME_HEIGHT -1 ){

                    return false;
                }
                if(cuteListArray[tmpX][tmpY]==1){

                    return false;
                }
            }
        }
    }
    return true;
}
void Widget::roteCute(){
    if(currentCuteType ==8){
        return;
    }
    if(!canCuteRote()){
        return;
    }
    int switchLen = 3;
    if(currentCuteType ==1 || currentCuteType ==2){
        switchLen=4;
    }
    int roteArray[4][4] = {0};

    for(int i=0;i<switchLen;i++){
        for(int j=0;j<switchLen;j++){
            roteArray[i][j]= currentCuteArray[j][switchLen-1-i];
        }
    }
    //
    for(int i=0;i<4;i++){
//        System.arraycopy(roteArray[i1], 0, currentCuteArray[i1], 0, 4);
        for (int j = 0; j < 4; ++j) {
            currentCuteArray[i][j] = roteArray[i][j];
        }
    }


}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_left_clicked()
{
    moveCute(0);
    this->setFocus();
}

void Widget::on_pushButton_right_clicked()
{
    moveCute(1);
    this->setFocus();
}

void Widget::on_pushButton_qucikmove_clicked()
{
    //快速移动
    isQucikMove = true;
    qDebug("ssss event");

    //快速移动
    for (int i = 0; i < 20; ++i) {
        if(!isQucikMove){
            break;
        }
        moveCute(2);
    }
    this->setFocus();
}

void Widget::on_pushButton_rota_clicked()
{
    roteCute();
    update();
    this->setFocus();
}

void Widget::on_pushButton_Reset_clicked()
{
    initGame();
    update();
    this->setFocus();
}

void Widget::on_pushButton_pause_clicked()
{
    if(!this->isPause){
       this->killTimer(timeId);
        isPause = true;
    }else{
        //重新开始计时器
        timeId = this->startTimer(1000);
        isPause = false;
    }
    this->setFocus();

}
