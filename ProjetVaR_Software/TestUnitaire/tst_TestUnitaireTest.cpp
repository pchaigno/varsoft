#include <QString>
#include <QtTest>

#include <QVector>
#include <QDateTime>
#include "Asset.h"
#include "Asset.cpp" // DEGEUX
#include "Portfolio.h"
#include "Portfolio.cpp"

class TestUnitaireTest : public QObject
{
    Q_OBJECT

public:
    TestUnitaireTest();

private Q_SLOTS:
    void testCase1();
    void testGetAsQVectors();
    void testPortfolioGetAsQVectors();
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
    QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate(QDate(2014, 1, 5), QTime(0, 0, 0));
    Asset test("test", "C:/Users/Ulysse/asset.txt", startDate, endDate);
    QVector<double> result = test.getAsQVectors(startDate, endDate);

    qDebug() << "size: " << result.size();
    qDebug() << "result.at(0): " << result.at(0);

    QVERIFY2(true, "Failure");
}

void TestUnitaireTest::testPortfolioGetAsQVectors()
{
    // FIRST ASSET DEFINITION
    QDateTime startDate1(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate1(QDate(2014, 1, 5), QTime(0, 0, 0));
    Asset asset1("test", "C:/Users/Ulysse/asset.txt", startDate1, endDate1);

    // SECOND ASSET DEFINITION
    QDateTime startDate2(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate2(QDate(2014, 1, 5), QTime(0, 0, 0));
    Asset asset2("test", "C:/Users/Ulysse/asset.txt", startDate2, endDate2);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
    //assets.insert(std::pair<Asset*,int>(&asset1, 1));
    assets.insert(&asset1, 1);
    //assets.insert(std::pair<Asset*,int>(&asset1, 2));
    assets.insert(&asset2, 2);

    QVector<Report> reports;
    Portfolio testPortfolio("testPortfolio", assets, reports);

    QVector<double> result = testPortfolio.getAsVectors(startDate1, endDate1);

    qDebug() << result.size();

    for(QVector<double>::const_iterator it=result.begin(); it!=result.end(); ++it) {
        qDebug() << *it;
    }

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestUnitaireTest)

#include "tst_TestUnitaireTest.moc"
