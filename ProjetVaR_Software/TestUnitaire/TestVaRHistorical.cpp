#include "TestVaRHistorical.h"

TestVaRHistorical::TestVaRHistorical()
{
}

void TestVaRHistorical::testExecute() {

    QString assetFolder = "../../CSV_examples/";

    // FIRST ASSET DEFINITION
    QDateTime startDate1(QDate(2014, 1, 1), QTime(0, 0, 0));
    QDateTime endDate1(QDate(2014, 1, 15), QTime(0, 0, 0));
    Asset asset1("asset1", assetFolder+"asset4.txt", startDate1, endDate1);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
    assets.insert(&asset1, 1);
    //assets.insert(&asset2, 2);
    //assets.insert(&asset3, 3);

    QVector<Report> reports;
    Portfolio testPortfolio("testPortfolio", assets, reports);

    VaRHistorical test(testPortfolio, 0.05);
    double var = test.execute(10);
    qDebug() << "VaR=" << var;


}
