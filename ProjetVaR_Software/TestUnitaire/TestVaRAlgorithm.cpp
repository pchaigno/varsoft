#include "TestVaRAlgorithm.h"

TestVaRAlgorithm::TestVaRAlgorithm() {
	QString assetFolder = "../../CSV_examples/";

	// ASSET DEFINITION
	QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset* dax = new Asset("dax", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(dax, 1);
	QVector<Report*> reports;
	this->daxPortfolio = Portfolio("daxPortfolio", assets, reports);
}
