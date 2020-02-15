#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringListIterator>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QItemSelectionModel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");

    //initNameTableModel();
}
void Widget::initNameTableModel(QStringList *list){
    nameModel = new QStandardItemModel(this);
    for (int i = 0; i < list->size(); ++i) {
        QStandardItem *item = new QStandardItem(list->at(i));
        nameModel->appendRow(item);
    }

    ui->listViewTableName->setModel(nameModel);
    ui->listViewTableName->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->listViewTableName,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
}
void Widget::openDataBase(QString name){
    qDebug()<<"name :"<<name;

    db.setDatabaseName(name);

    if(!db.open()){
        QMessageBox::warning(this,"error","打开数据库失败");
        return;
    }

    //获取数据库中的表
    QStringList strList =  db.tables();
    qDebug()<<"strList  "<<strList.count();
    initNameTableModel(&strList);


}
void Widget::showClick(QModelIndex index){
    qDebug()<<index.data().toString();
    //设置model
    tableModel = NULL;
    tableModel = new QSqlTableModel(this);
    tableModel->setTable(index.data().toString());
    //手动提交动作
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //把model 放在view
    ui->tableViewTableData->setModel(tableModel);
    //显示model里的数据
    tableModel->select();
}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButtonOpenFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");

    openDataBase(filePath);
}

void Widget::on_pushButtonConfm_clicked()
{
    //提交所有动作
    tableModel->submitAll();
}

void Widget::on_pushButtonCancel_clicked()
{
    //取消所有动作
    tableModel->revertAll();
}

void Widget::on_pushButton_clicked()
{
    //添加空记录
    QSqlRecord record = tableModel->record();
    //获取行号
    int row= tableModel->rowCount();
    tableModel->insertRecord(row,record);
}

void Widget::on_pushButtonDelete_clicked()
{
    //获取选中的模型
    QItemSelectionModel *selectedModel = ui->tableViewTableData->selectionModel();
   //取出model中的索引
   QModelIndexList list = selectedModel->selectedRows();
   //删除数据
   for (int i = 0; i < list.size(); ++i) {
       tableModel->removeRow(list.at(i).row());
   }
}

void Widget::on_pushButtonFind_clicked()
{
    QString name = ui->lineEditSearch->text();

    //名字字符串要加单引号
    tableModel->setFilter(QString("name = '%1'").arg(name));
    tableModel->filter();
    tableModel->select();
}
