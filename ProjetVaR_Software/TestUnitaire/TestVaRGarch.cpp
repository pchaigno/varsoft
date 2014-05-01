#include "TestVaRGarch.h"

TestVaRGarch::TestVaRGarch() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDateTime startDate1(QDate(2012, 1, 3), QTime(0, 0, 0));
	QDateTime endDate1(QDate(2014, 4, 17), QTime(0, 0, 0));
	Asset* asset1 = new Asset("asset1", assetFolder+"dax140417.csv", "YAHOO", startDate1, endDate1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QVector<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
}

void TestVaRGarch::testExecute() {

	// GarchModel parameters
	QDateTime date = this->father.retrieveEndDate();
	int period = 200;

	// VaRGarch parameters
	double risk = 0.05;
	int timeHorizon = 1;
	GarchModel garchModel = RInterface::computeGarchModel(this->father, date, period);
	int scenarios = 200;

	VaRGarch varGarch(this->father, risk, timeHorizon, garchModel, scenarios, false, 0);

	double var = varGarch.execute(date);
	qDebug() << "Value-at-Risk: " << var;
}
