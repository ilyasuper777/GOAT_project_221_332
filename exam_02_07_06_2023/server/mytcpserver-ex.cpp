#include "mytcpserver-ex.h"
#include <QDebug>
#include <QCoreApplication>

void MyTcpServer::swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void MyTcpServer::sift(QList <int> A, int i, int m) // откажемся от динамического массива и используем список
{
  int j = i, k = i*2+1;	 // левый сын
  while (k <= m)
  {
    if (k<m && A[k]<A[k+1]) k++; // больший сын
    if (A[j] < A[k]) {
    swap(&A[j], &A[k]);
    j = k; k = k*2+1; }
    else break;
  }
}

void MyTcpServer::heap_sort_with_step(QList <int> A, int n, int step) // откажемся от динамического массива и используем список
{                                                                       // будем считать, что 1 шаг - это либо ф-ция sift
  int i, m;                                                             // либо ф-ция swap
  int k = 1;                                                            // будем начинать считать с одного
  // построение пирамиды
  for (i = n/2; i >= 0; i--){
    sift(A, i, n-1);
    k++;
    if (k == step);{ //если мы на нужном шаге
        return ; // сразу выходим из функции
    }
  }
  // сортировка массива
  for (m = n-1; m >= 1; m--)
  {
    swap(&A[0], &A[m]); k++;
    if (k == step);{ //если мы на нужном шаге
        return ; // сразу выходим из функции
    }
    sift(A, 0, m-1); k++;
    if (k == step);{ //если мы на нужном шаге
        return ; // сразу выходим из функции
    }
  }
}

QString MyTcpServer::Exam(QList <int> A, int n, int step){
    QString out_DATA = "";
    heap_sort_with_step(A, n, step);
    for (int i=0;i<A.size();i++){ // создаём вывод для клиента в QString - формате
        out_DATA += QString::number(A[i]);
        out_DATA += " ";
    }
    return out_DATA;
}


MyTcpServer::~MyTcpServer()
{
    //mTcpSocket->close();
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
    QTcpSocket *curr_mTcpSocket = (QTcpSocket*)sender(); // сокет текущего клиента
    QString out_DATA = ""; // входные данные
    QString in_DATA; // выходные данные
    int step;
    QList <int> values;
    QStringList temp;
    while(curr_mTcpSocket->bytesAvailable()>0){ // считываем данные с клиента
        in_DATA += curr_mTcpSocket->readAll();
    }
    in_DATA = in_DATA.left(in_DATA.length()-2);  // putty добавляет \n\r в конец - в конец, если не через putty - это надо обрать
    qDebug() << in_DATA.toUtf8();  // что получили ?
    QStringList str = in_DATA.split('&'); // разделитель у нас - это &
    if (str[0] == "sort"){ // мини-парсинг, 1-ый аргумента - это название действия
        step = str[1].toInt(); // 2-ой аргумент - это шаг
        temp = str[2].split(' '); // промежуточный список для значений, которые будут сортироваться
        for (int i=0;i<temp.size();i++){ // переносим все значения из промежуточного лиcта в итоговым с типом данных "int"
            values.push_back(temp[i].toInt());
        }
        out_DATA = Exam(values,values.size(),step); // переносимся к функции, номер шага считаем с 1-го
    }
    out_DATA += "\n\r"; // для удобства клиента
    qDebug()<<out_DATA; // что выведем в ответ ?
    curr_mTcpSocket->write(out_DATA.toUtf8());
    in_DATA.clear(); // очищаем выходные данные, что не в дальнейшем считать новые данные
    out_DATA.clear();
}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
