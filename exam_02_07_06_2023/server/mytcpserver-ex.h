#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QList>
#include <QStringList>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    void swap(int *a, int *b);
    void sift(QList <int> A, int i, int m);
    void heap_sort_with_step(QList <int> A, int n, int step);
    QString Exam(QList <int> A, int n, int step);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    //void slotReadClient();
private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    int server_status;
};
#endif // MYSERVER_H







