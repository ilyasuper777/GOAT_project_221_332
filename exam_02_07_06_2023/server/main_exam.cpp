#include <QCoreApplication>
#include "mytcpserver-ex.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;

    return a.exec();
}
