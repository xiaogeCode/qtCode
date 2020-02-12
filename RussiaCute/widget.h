#ifndef WIDGET_H
#define WIDGET_H
#define GAME_WIDTH 8
#define GAME_HEIGHT 15
#define CUTE_LEN 40

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_qucikmove_clicked();

    void on_pushButton_rota_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_pause_clicked();

private:
    Ui::Widget *ui;
    //当前下降在方块
    int currentCuteArray[4][4];
    //下一个方块
    int nextCuteArray[4][4];
    //留在界面上在方块
    int cuteListArray[GAME_WIDTH][GAME_HEIGHT];
    //随机随机方块所在位置
    int currentX;
    //随机随机方块所在位置
    int currentY;
    //当前随机方块在类型
    int currentCuteType;
    //下一个随机方块类型
    int nextCuteType;
    //计数器id
    int timeId;
    //快速移动标志位
    bool isQucikMove;
    //游戏暂停标志
    bool isPause;


    //随机生成方块
    void createRandomCute();
    //判断随机方块是否可移动 可以移动返回true
    bool canCuteMove(int direction);
    //移动随机方块
    void moveCute(int direction);
    //是否已经到底了
    bool isCuteToBotom();
    //随机方块碰底后的处理
    void handleToCuteToBotom();
    //消除所有可以消去的方块
    void dismissCutes();
    //某一行在方块是否可以消去
    bool canCuteMiss(int row);
    //消去某一行方块
    void dissmissCuteLine(int row);
    //随机方块是否可以翻转
    bool canCuteRote();
    //翻转随机方块
    void roteCute();

    //初始化游戏
    void initGame();
};
#endif // WIDGET_H
