#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

QString MyTcpServer::exam(QStringList ans){
    QStringList temp; // вспомогательный массив для считывания абциссы и ординаты в вектор
    QVector<int> ver; // вершины
    if (ans[0] == "perimetr"){ // периметр
        double perimetr = 0;
        ans.pop_front();
        for (int i=0;i<ans.size();i++){ // проходимся по всем координатам, чтобы создать двумерный массив
             temp = ans[i].split(","); // 2 вершины в Qsting, двумерный маасив получается
             ver.append(temp[0].toInt()); // абцисса координаты
             ver.append(temp[1].toInt()); // ордината координаты
             temp.clear();
        }
        for (int i=1;i<(ver.size()/2);i++){ // проходимся по координатам со второй по последнюю
            perimetr += sqrt((ver[i*2]-ver[(i-1)*2])*(ver[i*2]-ver[(i-1)*2]) + (ver[i*2+1]-ver[(i-1)*2+1])* (ver[i*2+1]-ver[(i-1)*2+1]));
        }
        perimetr += sqrt((ver[0]-ver[(ver.size()/2-1)*2])*(ver[0]-ver[(ver.size()/2-1)*2]) + (ver[1]-ver[(ver.size()/2-1)*2+1])* (ver[1]-ver[(ver.size()/2-1)*2+1]));
        ver.clear();
        return QString::number(perimetr);
    }
    if (ans[0] == "area"){ // площадь
        double x,y,z;
        ans.pop_front();
        double area = 0;
        double semi_perimetr;
        for (int i=0;i<ans.size();i++){ // проходимся по всем координатам, чтобы создать двумерный массив
            temp = ans[i].split(","); // 2 вершины в Qsting, двумерный маасив получается
            ver.append(temp[0].toInt()); // абцисса
            ver.append(temp[1].toInt()); // ордината
            temp.clear();
        }
        for (int i=1;i<(ans.size()-1);i++){ // в n-угольнике, n-2 - треугольника
            x = sqrt((ver[i*2]-ver[(i-1)*2])*(ver[i*2]-ver[(i-1)*2] + (ver[i*2+1]-ver[(i-1)*2 + 1])*(ver[i*2+1]-ver[(i-1)*2 + 1])));
            y = sqrt((ver[(i+1)*2]-ver[(i-1)*2])*(ver[(i+1)*2]-ver[(i-1)*2] + (ver[(i+1)*2+1]-ver[(i-1)*2 + 1])*(ver[(i+1)*2+1]-ver[(i-1)*2 + 1])));
            x = sqrt((ver[i*2]-ver[(i+1)*2])*(ver[i*2]-ver[(i+1)*2] + (ver[i*2+1]-ver[(i+1)*2 + 1])*(ver[i*2+1]-ver[(i+1)*2 + 1])));
            semi_perimetr = (x+y+z)/2;
            area += sqrt(semi_perimetr*(semi_perimetr-x)*(semi_perimetr-y)*(semi_perimetr-z));
        }
        return QString::number(area);
    }
    ver.clear();
    return "None";
};

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(mTcpSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket *curr_mTcpSocket = (QTcpSocket*)sender();
       QString out_DATA;
       QString in_DATA;
       in_DATA.clear();

       while(curr_mTcpSocket->bytesAvailable()>0)
       {
           in_DATA += curr_mTcpSocket->readAll();
       }
       qDebug() << in_DATA.toUtf8();
       in_DATA = in_DATA.left(in_DATA.length()-2);  // может не пригодиться
       QStringList ans1 = in_DATA.split("@");
       out_DATA = exam(ans1);
       qDebug()<<out_DATA.toUtf8();
       curr_mTcpSocket->write(out_DATA.toUtf8());
}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
