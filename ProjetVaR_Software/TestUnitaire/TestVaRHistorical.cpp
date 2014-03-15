#include "TestVaRHistorical.h"

TestVaRHistorical::TestVaRHistorical()
{
}

void TestVaRHistorical::testExecute() {

    QString assetFolder = "../../CSV_examples/";

	// ASSET DEFINITION
	QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset dax("dax", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
	assets.insert(&dax, 1);
	QVector<Report*> reports;
	Portfolio daxPortfolio("daxPortfolio", assets, reports);

	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 20;
	VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);

	double var;

	try {
		var = daxVaR.execute(endDate);
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	qDebug() << "At the following date: " + endDate.toString();
	qDebug() << "For the asset: " + dax.getName();
	qDebug() << "Historical VaR parameters: risk=" << risk << ", timeHorizon=" << timeHorizon << "returnsPeriod=" << returnsPeriod;
	qDebug() << "Value-at-Risk=" << var;
}
