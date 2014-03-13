#include "TestVaRHistorical.h"

TestVaRHistorical::TestVaRHistorical()
{
}

void TestVaRHistorical::testExecute() {

    QString assetFolder = "../../CSV_examples/";

    // FIRST ASSET DEFINITION
	QDateTime startDate1(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate1(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset asset1("dax", assetFolder+"dax.csv", "YAHOO", startDate1, endDate1);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
    assets.insert(&asset1, 1);
    //assets.insert(&asset2, 2);
    //assets.insert(&asset3, 3);

	QVector<Report*> reports;
    Portfolio testPortfolio("testPortfolio", assets, reports);

    VaRHistorical test(testPortfolio, 0.05);

	double var;

	try {
		var = test.execute(10);
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}
    qDebug() << "VaR=" << var;


}
