#include "TestVaRGarch.h"

TestVaRGarch::TestVaRGarch() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDateTime startDate1(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate1(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset* asset1 = new Asset("asset1", assetFolder+"dax.csv", "YAHOO", startDate1, endDate1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QVector<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
}

void TestVaRGarch::testExecute() {

	// GarchModel parameters
	QDateTime date = this->father.retrieveEndDate();
	int period = 20;

	// VaRGarch parameters
	double risk = 0.05;
	int timeHorizon = 1;
	GarchModel garchModel = RInterface::computeGarchModel(this->father, date, period);
	int scenarios = 100;

	VaRGarch varGarch(this->father, risk, timeHorizon, garchModel, scenarios);

	double var = varGarch.execute(date);
	qDebug() << var;
}
