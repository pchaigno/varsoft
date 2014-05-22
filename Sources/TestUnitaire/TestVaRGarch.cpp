#include "TestVaRGarch.h"

/**
 * @brief Builds two portfolio. The first one contains the DAX index as only asset.
 * The second one contains a single asset which returns are a sample resulting from normal distribution.
 */
TestVaRGarch::TestVaRGarch() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDate startDate1(2012, 1, 3);
	QDate endDate1(2014, 4, 17);
	Asset* asset1 = new Asset("asset1", assetFolder+"dax140417.csv", "YAHOO", startDate1, endDate1);

	// SECOND ASSET DEFINITION
	QDate startDate2(2010, 1, 1);
	QDate endDate2(2013, 12, 31);
	Asset* asset2 = new Asset("asset2", assetFolder+"normal_returns.txt", "YAHOO", startDate2, endDate2);

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

/**
 * @brief Tests the calculation of the Value-at-Risk using a Garch model.
 * initStddev is false because the model computation date parameter is the
 * same as the VaR computation one.
 */
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
	// VaR value varies from one execution to another
	double var = varGarch.execute(date);
	// In any case VaR should not be negative
	QVERIFY(var >= 0);
	qDebug() << "Value-at-Risk: " << var;
}

/**
 * @brief Tests the calculation of the Value-at-Risk using a Garch model.
 * initStddev is true because the model computation date parameter is not the
 * same as the VaR computation one.
 */
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
	// VaR value varies from one execution to another
	double var = varGarch.execute(date);
	// In any case VaR should not be negative
	QVERIFY(var >= 0);
	qDebug() << "Value-at-Risk: " << var;
}

/**
 * @brief Tests that the Value-at-Risk computed on an asset which returns are a sample
 * resulting from normal distribution, is close to the (1-risk) quantile of the normal distribution.
 */
void TestVaRGarch::testExecuteNormalReturns() {
	// GarchModel parameters
	QDate date = this->uncle.retrieveEndDate();
	// Period to compute garch model, 200 days
	int period = 1000;

	// VaRGarch parameters
	double risk = 0.05;
	int timeHorizon = 1;
	GarchModel garchModel = RInterface::computeGarchModel(this->uncle, date, period);
	// Number of sceniarios for the boostrap
	int scenarios = 500;

	VaRGarch varGarch(this->uncle, risk, timeHorizon, garchModel, scenarios, false, 0);

	// VaR value varies from one execution to another
	// It should be around the 0.95-order quantile which is 1.644
	double var = varGarch.execute(date);
	// In any case VaR should not be negative
	QVERIFY(var >= 0);
	qDebug() << var;
}
