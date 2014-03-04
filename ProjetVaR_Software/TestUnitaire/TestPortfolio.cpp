#pragma once

#include "TestPortfolio.h"

TestPortfolio::TestPortfolio() {}

void TestPortfolio::testGetAsQVectors() {

    QString assetFolder = "../../CSV_examples/";

    // FIRST ASSET DEFINITION
    QDateTime startDate1(QDate(2014, 1, 1), QTime(0, 0, 0));
    QDateTime endDate1(QDate(2014, 1, 6), QTime(0, 0, 0));
    Asset asset1("asset1", assetFolder+"asset1.txt", startDate1, endDate1);

    // SECOND ASSET DEFINITION
    QDateTime startDate2(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate2(QDate(2014, 1, 7), QTime(0, 0, 0));
    Asset asset2("asset2", assetFolder+"asset2.txt", startDate2, endDate2);

    // THIRD ASSET DEFINITION
    QDateTime startDate3(QDate(2014, 1, 3), QTime(0, 0, 0));
    QDateTime endDate3(QDate(2014, 1, 8), QTime(0, 0, 0));
    Asset asset3("asset3", assetFolder+"asset3.txt", startDate3, endDate3);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
    assets.insert(&asset1, 1);
    assets.insert(&asset2, 2);
    assets.insert(&asset3, 3);

    QVector<Report> reports;
    Portfolio testPortfolio("testPortfolio", assets, reports);

    // COMMON DATE DEFINITION
    QDateTime startDate(QDate(2014, 1, 3), QTime(0, 0, 0));
    QDateTime endDate(QDate(2014, 1, 6), QTime(0, 0, 0));

    QVector<double> result = testPortfolio.getAsQVectors(startDate, endDate);

    QCOMPARE(result.size(), 4);
    QCOMPARE(result.at(0), 612.0);
    QCOMPARE(result.at(1), 618.0);
    QCOMPARE(result.at(2), 624.0);
    QCOMPARE(result.at(3), 630.0);

    for(QVector<double>::const_iterator it=result.begin(); it!=result.end(); ++it) {
        qDebug() << *it;
    }
}

