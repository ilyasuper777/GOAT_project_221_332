#include <QtTest>
#include "../../server/mytcpserver.h"

// add necessary includes here

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test();

private slots:
    void test_case1();
    void test_case2();
};

test::test()
{

}

test::~test()
{

}

void test::test_case1()
{
    MyTcpServer a;
    QStringList str;
    str.append("perimetr");
    str.append("1,2");
    str.append("2,3");
    str.append("3,4");
    str.append("4,5");
    str.append("5,6");
    str.append("6,7");
    str.append("7,8");
    str.append("8,9");
    str.append("9,10");
    str.append("10,11/n");
    QCOMPARE(a.exam(str),"30.5831");
}

void test::test_case2()
{
    MyTcpServer a;
    QStringList str;
    str.append("area");
    str.append("3,4");
    str.append("4,1");
    str.append("5,4");
    str.append("6,5");
    str.append("7,6");
    str.append("8,7");
    str.append("9,8");
    str.append("10,9");
    str.append("11,10");
    str.append("12,11/n");
    QCOMPARE(a.exam(str),"nan");
}

QTEST_APPLESS_MAIN(test)

#include "tst_test.moc"
