#ifndef WIDGET_H
#define WIDGET_H
//#define RECT_WIDTH 40
//#define RECT_HEIGHT 40
#define GAME_WIDTH 600
#define GAME_HEIGHT 800
#include <QWidget>
#include"rgbvalue.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_Reset_clicked();

    void on_pushButton_tip_clicked();

private:
    Ui::Widget *ui;
    //原来颜色数据
    QList<RgbValue> origionRgbList;
    //改变后颜色数据
    QList<RgbValue> changedRgbList;
    //水平长度
    int horizon;
    //竖直长度
    int verizon;
    //保存改变数据在List的位置
    int changedIndex;
    //展示提示标识
    bool isShowTips;
    //颜色块宽
    int rectWidth;
    //颜色块高
    int rectHeight;

    //随机生成一种rgb颜色
    RgbValue randomRgb();
    //根据宽，高生成俩个图片的数据
    void createListData(int w,int h);
    //初始化游戏数据
    void initGame();
};
#endif // WIDGET_H
