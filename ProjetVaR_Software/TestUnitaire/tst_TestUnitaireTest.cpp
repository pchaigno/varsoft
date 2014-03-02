#include <QString>
#include <QtTest>

#include <QVector>
#include <QDateTime>
#include "Asset.h"
#include "Asset.cpp" // DEGEUX

class TestUnitaireTest : public QObject
{
    Q_OBJECT

public:
    TestUnitaireTest();

private Q_SLOTS:
    void testCase1();
    void testGetAsQVectors();
};

TestUnitaireTest::TestUnitaireTest()
{
}

void TestUnitaireTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

void TestUnitaireTest::testGetAsQVectors()
{
    QDateTime startDate(QDate(2014, 1, 1), QTime(0, 0, 0));
    QDateTime endDate(QDate(2014, 1, 5), QTime(0, 0, 0));
    Asset test("test", "C:/Users/Ulysse/asset.txt", startDate, endDate);
    QVector<double> result = test.getAsQVectors(startDate, endDate);

    //qDebug() << result.at(0);

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestUnitaireTest)

#include "tst_TestUnitaireTest.moc"
