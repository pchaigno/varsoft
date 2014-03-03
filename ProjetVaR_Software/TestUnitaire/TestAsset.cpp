#include "Asset.h"
//#include "Asset.cpp"
#include "TestAsset.h"
#include <QVector>

TestAsset::TestAsset() {}

void TestAsset::testGetAsQVectors() {

    QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate(QDate(2014, 1, 5), QTime(0, 0, 0));

    QString assetFolder = "C:/Users/Ulysse/ProjetVaR/CSV_examples/";
    Asset test("test", assetFolder+"asset1.txt", startDate, endDate);

    QVector<double> result = test.getAsQVectors(startDate, endDate);

    QVERIFY(result.size() == 4);
    QVERIFY(result.at(0) == 101);
    QVERIFY(result.at(1) == 102);
    QVERIFY(result.at(2) == 103);
    QVERIFY(result.at(3) == 104);
}
