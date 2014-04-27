/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "TestPortfolio.h"

/**
 * @brief Initializes a few portfolio for the tests.
 */
TestPortfolio::TestPortfolio() {
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDate startDate1(2014, 1, 1);
	QDate endDate1(2014, 1, 6);
	Asset* asset1 = new Asset("asset1", assetFolder+"asset1.txt", "YAHOO", startDate1, endDate1);

	// SECOND ASSET DEFINITION
	QDate startDate2(2014, 1, 2);
	QDate endDate2(2014, 1, 7);
	Asset* asset2 = new Asset("asset2", assetFolder+"asset2.txt", "YAHOO", startDate2, endDate2);

	// THIRD ASSET DEFINITION
	QDate startDate3(QDate(2014, 1, 3));
	QDate endDate3(QDate(2014, 1, 8));
	Asset* asset3 = new Asset("asset3", assetFolder+"asset3.txt", "YAHOO", startDate3, endDate3);

	// FOURTH ASSET DEFINITION
	QDate startDate4(QDate(2013, 12, 19));
	QDate endDate4(QDate(2014, 1, 2));
	Asset* asset4 = new Asset("asset4", assetFolder+"asset4.txt", "YAHOO", startDate4, endDate4);

	// FIFTH ASSET DEFINITION
	QDate startDate5(QDate(2013, 12, 19));
	QDate endDate5(QDate(2014, 1, 3));
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
		QFAIL("No exception thrown when attributed an id to a porfolio twice.");
	} catch(const IdAlreadyAttributedException e) {

	}
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
 * @brief Tests the retrieveStartDate method.
 */
void TestPortfolio::testRetrieveStartDate() {
	QCOMPARE(this->father.retrieveStartDate(), QDate(2014, 1, 3));
	QCOMPARE(this->son.retrieveStartDate(), QDate(2014, 1, 3));
	QCOMPARE(this->uncle.retrieveStartDate(), QDate(2013, 12, 19));
}

/**
 * @brief Tests the retrieveStartDate method.
 */
void TestPortfolio::testRetrieveEndDate() {
	QCOMPARE(this->father.retrieveEndDate(), QDate(2014, 1, 6));
	QCOMPARE(this->son.retrieveEndDate(), QDate(2014, 1, 6));
	QCOMPARE(this->uncle.retrieveEndDate(), QDate(2014, 1, 2));
}

/**
 * @brief Tests the method getValues that retrieve and compute values of a portfolio.
 */
void TestPortfolio::testRetrieveValues() {
	QVector<double> result = this->son.retrieveValues(QDate(2014, 1, 4), QDate(2014, 1, 6));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 630.0);
}

/**
 * @brief Successful test of retrieveValues without parameters.
 */
void TestPortfolio::testRetrieveValuesNoParameters() {
	QVector<double> result = this->son.retrieveValues();
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 630.0);
}

/**
 * @brief Tests the method retrieveValuesByDate that retrieve and compute date-values of a portfolio
 */
void TestPortfolio::testRetrieveValuesByDate() {
	QMap<QDate, double> result = this->son.retrieveValuesByDate(QDate(2014, 1, 4), QDate(2014, 1, 6));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.value(QDate(2014, 1, 6)), 630.0);
}

/**
 * @brief Tests of retrieveValuesByDate when the period is larger than the portfolio's period.
 */
void TestPortfolio::testRetrieveValuesByDateMissingValues() {
	QMap<QDate, double> result = this->son.retrieveValuesByDate(QDate(2014, 1, 2), QDate(2014, 1, 8));
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.value(QDate(2014, 1, 3)), 612.0);
	QCOMPARE(result.value(QDate(2014, 1, 6)), 630.0);
}

/**
 * @brief Tests the retrieveReturns method without parameters.
 * This method calls directly the eponymous method on the whole definition period of the portfolio.
 */
void TestPortfolio::testRetrieveReturns() {
	QVector<double> result = this->son.retrieveReturns();
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 18.0);
}

/**
 * @brief Tests the the retrieveReturns methods with a small number of values to return.
 * The portfolio son only contains 2 values (so only 1 returns).
 */
void TestPortfolio::testRetrieveNbReturnsNotEnough() {
	QVector<double> result = this->son.retrieveReturns(this->son.retrieveEndDate(), 2);
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 18.0);
}

/**
 * @brief Tests the the retrieveReturns methods with a small number of values to return.
 * The portfolio uncle contains 11 values (so 10 returns).
 * This test retrieves all returns.
 */
void TestPortfolio::testRetrieveNbReturnsAll() {
	QVector<double> result = this->uncle.retrieveReturns(this->uncle.retrieveEndDate(), 10);
	QCOMPARE(result.size(), 10);
	QCOMPARE(result.at(0), 20.0);
	QCOMPARE(result.at(1), 2.0);
	QCOMPARE(result.at(2), 2.0);
	QCOMPARE(result.at(3), 2.0);
	QCOMPARE(result.at(4), 5.0);
	QCOMPARE(result.at(5), -20.0);
	QCOMPARE(result.at(6), 11.0);
	QCOMPARE(result.at(7), 0.0);
	QCOMPARE(result.at(8), 4.0);
	QCOMPARE(result.at(9), 1.0);
}

/**
 * @brief Tests the the retrieveReturns methods with a small number of values to return.
 * The portfolio uncle contains 11 values (so 10 returns).
 * This test only retrieves 4 returns.
 */
void TestPortfolio::testRetrieveNbReturnsSome() {
	QVector<double> result = this->uncle.retrieveReturns(this->uncle.retrieveEndDate(), 4);
	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 11.0);
	QCOMPARE(result.at(1), 0.0);
	QCOMPARE(result.at(2), 4.0);
	QCOMPARE(result.at(3), 1.0);
}
