#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //初始化表面列表
    void initNameTableModel(QStringList *list);
    void openDataBase(QString name);
private slots:
    void showClick(QModelIndex);
    void on_pushButtonOpenFile_clicked();

    void on_pushButtonConfm_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButton_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonFind_clicked();

private:
    Ui::Widget *ui;
    //数据库表名数据
    QStandardItemModel *nameModel;
    //数据库文件名
    QFile fileName;
    //数据库
    QSqlDatabase db;
    //表的数据
    QSqlTableModel *tableModel;
};
#endif // WIDGET_H
