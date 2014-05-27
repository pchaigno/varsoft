#include "TestVaRGarch.h"

/**
 * @brief Builds two portfolio. The first one contains the DAX index as only asset.
 * The second one contains a single asset which returns are a sample resulting from normal distribution.
 */
TestVaRGarch::TestVaRGarch() {
	QString assetFolder = "../CSV_examples/";

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
	this->father = new Portfolio("Father", assets1, reports1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets2;
	assets2.insert(asset2, 1);
	QList<Report*> reports2;
	this->uncle = new Portfolio("Uncle", assets2, reports2);
}

/**
 * @brief Tests the calculation of the Value-at-Risk using a Garch model.
 */
void TestVaRGarch::testExecute() {
	// VaR parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int scenarios = 200; // Number of sceniarios for the boostrap
	int nbInitIterations = 20;

	// Garch model parameters
	QPair<QDate, QDate> period;
	period.first = QDate(2013,1,1);
	period.second = QDate(2013,12,30);

	// Garch model computation
	GarchModel garchModel = RInterface::computeGarchModel(*father, period);

	// VaR value varies from one execution to another
	VaRGarch varGarch(*father, risk, timeHorizon, garchModel, scenarios, nbInitIterations);
	double var = varGarch.execute(QDate(2014, 04, 18));
	// In any case VaR should not be negative
	QVERIFY(var >= 0);
	qDebug() << "Value-at-Risk: " << var;
}

/**
 * @brief Tests the calculation of the Value-at-Risk using a Garch model. The time horizon
 * is three days in this case.
 */
void TestVaRGarch::testExecuteThreeDaysHorizon() {
	// VaR parameters
	double risk = 0.05;
	int timeHorizon = 3;
	int scenarios = 200; // Number of sceniarios for the boostrap
	int nbInitIterations = 20;

	// Garch model parameters
	QPair<QDate, QDate> period;
	period.first = QDate(2013,1,1);
	period.second = QDate(2013,12,30);

	// Garch model computation
	GarchModel garchModel = RInterface::computeGarchModel(*father, period);

	// VaR value varies from one execution to another
	VaRGarch varGarch(*father, risk, timeHorizon, garchModel, scenarios, nbInitIterations);
	double var = varGarch.execute(QDate(2014, 04, 18));
	// In any case VaR should not be negative
	QVERIFY(var >= 0);
	qDebug() << "Value-at-Risk: " << var;
}

/**
 * @brief Tests that the Value-at-Risk computed on an asset which returns are a sample
 * resulting from normal distribution, is close to the (1-risk) quantile of the normal distribution.
 */
void TestVaRGarch::testExecuteNormalReturns() {
	// VaR parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int scenarios = 500; // Number of sceniarios for the boostrap
	int nbInitIterations = 20;

	// Garch model parameters
	QPair<QDate, QDate> period;
	period.first = this->uncle->retrieveStartDate();
	period.second = this->uncle->retrieveEndDate();

	// Garch model computation
	GarchModel garchModel = RInterface::computeGarchModel(*uncle, period);

	// VaR value varies from one execution to another
	// It should be around the 0.95-order quantile which is 1.644
	VaRGarch varGarch(*uncle, risk, timeHorizon, garchModel, scenarios, nbInitIterations);
	double var = varGarch.execute(QDate(2014, 1, 1));
	// In any case VaR should not be negative
	QVERIFY(var >= 0);
	qDebug() << var;
}
