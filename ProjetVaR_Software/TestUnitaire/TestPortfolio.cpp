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
void TestPortfolio::testGetValues() {
	// COMMON DATE DEFINITION
	QDateTime startDate(QDate(2014, 1, 3), QTime(0, 0, 0));
	QDateTime endDate(QDate(2014, 1, 6), QTime(0, 0, 0));
	// INCORRECT DATE DEFINITION
	QDateTime incorrectStartDate(QDate(2014, 1, 1), QTime(0, 0, 0));

	QVector<double> result;

	// getValues() version with dates parameters
	try {
		result = this->son.getValues(startDate, endDate);
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 618.0);
	QCOMPARE(result.at(2), 624.0);
	QCOMPARE(result.at(3), 630.0);

	for(QVector<double>::const_iterator it=result.begin(); it!=result.end(); ++it) {
		qDebug() << *it;
	}

	// getValues() version without parameters
	try {
		result = this->son.getValues();
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 618.0);
	QCOMPARE(result.at(2), 624.0);
	QCOMPARE(result.at(3), 630.0);

	for(QVector<double>::const_iterator it=result.begin(); it!=result.end(); ++it) {
		qDebug() << *it;
	}

	// getValuesByDates()
	QMap<QDateTime, double> result2;

	try {
		result2 = this->son.getValuesByDates2(startDate, endDate);
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 618.0);
	QCOMPARE(result.at(2), 624.0);
	QCOMPARE(result.at(3), 630.0);

	for(QMap<QDateTime, double>::const_iterator it=result2.begin(); it!=result2.end(); ++it) {
		qDebug() << it.key() << it.value();
	}



	// getValuesByDates2()
	QMap<QDateTime, double> result3;
	result3 = this->uncle.getValuesByDates2(QDateTime(QDate(2014, 1, 1), QTime(0, 0, 0)), QDateTime(QDate(2014, 1, 4), QTime(0, 0, 0)));

	for(QMap<QDateTime, double>::const_iterator it=result3.begin(); it!=result3.end(); ++it) {
		qDebug() << it.key() << it.value();
	}

	// INCORRECT DATE CASE FOR ILLUSTRATION PURPOSES
	try {
		result = this->son.getValues(incorrectStartDate, endDate);
		QFAIL("getValues() was able to calculate the portfolio values with missing asset values");
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}
}
