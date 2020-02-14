#include "serverwidget.h"
#include "socketclientwidget.h".h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    SocketClientWidget c;
    c.show();

    return a.exec();
}
