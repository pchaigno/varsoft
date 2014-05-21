#include "TestVaRGarch.h"

TestVaRGarch::TestVaRGarch() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDate startDate1(2012, 1, 3);
	QDate endDate1(2014, 4, 17);
	Asset* asset1 = new Asset("asset1", assetFolder+"dax140417.csv", "YAHOO", startDate1, endDate1);

	// SECOND ASSET DEFINITION
	QDate startDate2(2010, 1, 1);
	QDate endDate2(2013, 12, 31);
	Asset* asset2 = new Asset("asset2", assetFolder+"normvalues.txt", "YAHOO", startDate2, endDate2);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets1;
	assets1.insert(asset1, 1);
	QList<Report*> reports1;
	this->father = Portfolio("Father", assets1, reports1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets2;
	assets2.insert(asset2, 1);
	QList<Report*> reports2;
	this->uncle = Portfolio("Uncle", assets2, reports2);
}

void TestVaRGarch::testExecuteNoInit() {
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
}

void TestVaRGarch::testExecuteNorm() {
	// GarchModel parameters
	QDate date = this->uncle.retrieveEndDate();
	// Period to compute garch model, 200 days
	int period = 400;

	// VaRGarch parameters
	double risk = 0.05;
	int timeHorizon = 1;
	GarchModel garchModel = RInterface::computeGarchModel(this->uncle, date, period);
	// Number of sceniarios for the boostrap
	int scenarios = 200;

	VaRGarch varGarch(this->uncle, risk, timeHorizon, garchModel, scenarios, false, 0);

	double var = varGarch.execute(date);
	qDebug() << "Value-at-Risk: " << var;
}

void TestVaRGarch::testExecuteWithInit() {
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

	// Standard deviation initialization case
	VaRGarch varGarch(this->father, risk, timeHorizon, garchModel, scenarios, true, 20);
	double var = varGarch.execute(date);
	qDebug() << "Value-at-Risk: " << var;
}
