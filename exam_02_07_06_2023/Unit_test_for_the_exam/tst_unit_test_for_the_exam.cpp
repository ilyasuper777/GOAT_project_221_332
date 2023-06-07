#include <QtTest>
#include "../../server/mytcpserver-ex.h"
// add necessary includes here

class Unit_test_for_the_exam : public QObject
{
    Q_OBJECT

public:
    Unit_test_for_the_exam();
    ~Unit_test_for_the_exam();

private slots:
    void test_case1();
    void test_case2();
};

Unit_test_for_the_exam::Unit_test_for_the_exam()
{

}

Unit_test_for_the_exam::~Unit_test_for_the_exam()
{
}

void Unit_test_for_the_exam::test_case1()
{
    MyTcpServer b;
    QList <int> A;
    A.append(2);
    A.append(5);
    A.append(1);
    A.append(6);
    A.append(8);
    A.append(3);
    A.append(8);
    A.append(9);
    A.append(-2);
    A.append(-6);
    QCOMPARE(b.Exam(A,A.size(),7),"2 5 1 6 8 3 8 9 -2 -6 ");
}

void Unit_test_for_the_exam::test_case2()
{
    MyTcpServer b;
    QList <int> A;
    A.append(3);
    A.append(2);
    A.append(5);
    A.append(7);
    A.append(1);
    A.append(-3);
    A.append(4);
    A.append(-4);
    A.append(-2);
    A.append(1);
    QCOMPARE(b.Exam(A,A.size(),4),"3 2 5 7 1 -3 4 -4 -2 1 ");
}

QTEST_APPLESS_MAIN(Unit_test_for_the_exam)

#include "tst_unit_test_for_the_exam.moc"
