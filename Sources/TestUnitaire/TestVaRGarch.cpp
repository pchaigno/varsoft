#include "TestVaRGarch.h"

TestVaRGarch::TestVaRGarch() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDate startDate1(2012, 1, 3);
	QDate endDate1(2014, 4, 17);
	Asset* asset1 = new Asset("asset1", assetFolder+"dax140417.csv", "YAHOO", startDate1, endDate1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QVector<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
}

void TestVaRGarch::testExecute() {

	// GarchModel parameters
	QDate date = this->father.retrieveEndDate();
	// Period to compute garch model, 200 days
	int period = 200;

	// VaRGarch parameters
	double risk = 0.05;
	int timeHorizon = 1;
	GarchModel garchModel = RInterface::computeGarchModel(this->father, date, period);
	// Number of sceniarios for the boostrap
	int scenarios = 200;

	VaRGarch varGarch(this->father, risk, timeHorizon, garchModel, scenarios, false, 0);
	double var = varGarch.execute(date);
	qDebug() << "Value-at-Risk: " << var;

	// Standard deviation initialization case
	VaRGarch varGarchInit(this->father, risk, timeHorizon, garchModel, scenarios, true, 20);
	var = varGarchInit.execute(date);
	qDebug() << "Value-at-Risk: " << var;
}
