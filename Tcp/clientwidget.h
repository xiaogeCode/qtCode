#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui {
class ClientWidget;
}
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpSocket;
};

#endif // CLIENTWIDGET_H
