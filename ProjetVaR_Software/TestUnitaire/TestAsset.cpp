#include "TestAsset.h"

TestAsset::TestAsset() {}

void TestAsset::testGetAsQVectors() {

    QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate(QDate(2014, 1, 5), QTime(0, 0, 0));

    QString assetFolder = "../../CSV_examples/";
    Asset test("test", assetFolder+"asset1.txt", startDate, endDate);

    QVector<double> result = test.getAsQVectors(startDate, endDate);

    QCOMPARE(result.size(), 4);
    QCOMPARE(result.at(0), 101.0);
    QCOMPARE(result.at(1), 102.0);
    QCOMPARE(result.at(2), 103.0);
    QCOMPARE(result.at(3), 104.0);
}
