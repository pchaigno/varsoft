#include "TestPortfolio.h"

/**
 * @brief Initializes a few portfolio for the tests.
 */
TestPortfolio::TestPortfolio() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDateTime startDate1(QDate(2014, 1, 1), QTime(0, 0, 0));
	QDateTime endDate1(QDate(2014, 1, 6), QTime(0, 0, 0));
	Asset* asset1 = new Asset("asset1", assetFolder+"asset1.txt", "YAHOO", startDate1, endDate1);

	// SECOND ASSET DEFINITION
	QDateTime startDate2(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate2(QDate(2014, 1, 7), QTime(0, 0, 0));
	Asset* asset2 = new Asset("asset2", assetFolder+"asset2.txt", "YAHOO", startDate2, endDate2);

	// THIRD ASSET DEFINITION
	QDateTime startDate3(QDate(2014, 1, 3), QTime(0, 0, 0));
	QDateTime endDate3(QDate(2014, 1, 8), QTime(0, 0, 0));
	Asset* asset3 = new Asset("asset3", assetFolder+"asset3.txt", "YAHOO", startDate3, endDate3);

	// FOURTH ASSET DEFINITION
	QDateTime startDate4(QDate(2014, 1, 1), QTime(0, 0, 0));
	QDateTime endDate4(QDate(2014, 1, 4), QTime(0, 0, 0));
	Asset* asset4 = new Asset("asset4", assetFolder+"asset4.txt", "YAHOO", startDate4, endDate4);

	// FIFTH ASSET DEFINITION
	QDateTime startDate5(QDate(2014, 1, 1), QTime(0, 0, 0));
	QDateTime endDate5(QDate(2014, 1, 4), QTime(0, 0, 0));
	Asset* asset5 = new Asset("asset5", assetFolder+"asset5.txt", "YAHOO", startDate5, endDate5);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	assets.insert(asset2, 2);
	assets.insert(asset3, 3);

	QVector<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
	this->son = Portfolio(&this->father, "Son", assets, reports);

	// SECOND PORTFOLIO DEFINITION
	QMap<Asset*, int> assets2;
	assets2.insert(asset4, 1);
	assets2.insert(asset5, 2);
	QVector<Report*> reports2;
	this->uncle = Portfolio("uncle", assets2, reports2);
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestPortfolio::testId() {
	QCOMPARE(this->father.getId(), -1);
	QCOMPARE(this->son.getParentId(), -1);
	this->father.setId(42);
	QCOMPARE(this->father.getId(), 42);
	QCOMPARE(this->son.getParentId(), 42);
	try {
		this->father.setId(43);
	} catch(const IdAlreadyAttributedException e) {
		return;
	}
	QFAIL("No exception thrown when attributed an id to a porfolio twice.");
}

/**
 * @brief Checks that the name can actually be changed.
 */
void TestPortfolio::testName() {
	QVERIFY(this->father.getName() == "Father");
	this->father.changeName("John");
	QVERIFY(this->father.getName() == "John");
}

/**
 * @brief Tests the method getValues that retrieve and compute values of a portfolio.
 */
void TestPortfolio::testRetrieveValues() {
	// SHARED DATE DEFINITION
	QDateTime startDate(QDate(2014, 1, 3), QTime(0, 0, 0));
	QDateTime endDate(QDate(2014, 1, 6), QTime(0, 0, 0));

	QVector<double> result;

	// DATE PARAMETERS FUNCTION TESTS
	// EXPECTED USE CASE
	try {
		result = this->son.retrieveValues(startDate, endDate);
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 618.0);
	QCOMPARE(result.at(2), 624.0);
	QCOMPARE(result.at(3), 630.0);

	// NO PARAMETER FUNCTION TESTS
	try {
		result = this->son.retrieveValues();
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 6);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 618.0);
	QCOMPARE(result.at(2), 624.0);
	QCOMPARE(result.at(3), 630.0);
	QCOMPARE(result.at(4), 635.0);
	QCOMPARE(result.at(5), 638.0);
}

/**
 * @brief Tests the method retrieveValuesByDate that retrieve and compute date-values of a portfolio
 */
void TestPortfolio::testRetrieveValuesByDate() {
	// RetrieveValuesByDate() behaviour
	// FIRST PORTFOLIO ILLUSTRATION
	//				a1		a2		a3		Portfolio
	// 2014-01-01	100		UNDEF	UNDEF	UNDEF
	// 2014-01-02	101		202		UNDEF	UNDEF
	// 2014-01-03	102		204		306		612
	// 2014-01-04	103		206		309		618
	// 2014-01-05	104		208		312		624
	// 2014-01-06	105		210		315		630
	// 2014-01-07	UNDEF	212		318		635 << using previous value for a1
	// 2014-01-08	UNDEF	UNDEF	321		638 << using previous values for a1 and a2

	QMap<QDateTime, double> result;

	// EXPECTED USE CASE
	try {
		result = this->son.retrieveValuesByDate(QDateTime(QDate(2014, 1, 3), QTime(0, 0, 0)), QDateTime(QDate(2014, 1, 8), QTime(0, 0, 0)));
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 6);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 3), QTime(0, 0, 0))), 612.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 4), QTime(0, 0, 0))), 618.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 5), QTime(0, 0, 0))), 624.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 6), QTime(0, 0, 0))), 630.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 7), QTime(0, 0, 0))), 635.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 8), QTime(0, 0, 0))), 638.0);

	// UNDEFINED USE CASE
	try {
		result = this->son.retrieveValuesByDate(QDateTime(QDate(2014, 1, 2), QTime(0, 0, 0)), QDateTime(QDate(2014, 1, 8), QTime(0, 0, 0)));
		QFAIL("retrieveValuesByDate succedded in computing portfolio values despite missing asset values");
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}
}

void TestPortfolio::testRetrieveReturns() {
	QVector<double> result;

	result = this->son.retrieveReturns(QDateTime(QDate(2014, 1, 8), QTime(0, 0, 0)), 4);

	qDebug() << result;

	qDebug() << this->son.retrieveLastDate();
	result = this->son.retrieveReturns(this->son.retrieveLastDate(), 4);
	// In that case retrieveLastDate() is 2014-01-06 because it is the last shared date
	// among the assets.
	qDebug() << result;
}
