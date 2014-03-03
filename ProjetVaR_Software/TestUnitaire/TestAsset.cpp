//#pragma once
#include "Asset.h"
#include "Asset.cpp"
#include <QDebug>
#include <QString>
#include <QTest>
#include <QVector>

class TestAsset: public QObject {
    Q_OBJECT

public:
    TestAsset();

private Q_SLOTS:
    void testGetAsQVectors();

};

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

QTEST_APPLESS_MAIN(TestAsset)

#include "TestAsset.moc"
