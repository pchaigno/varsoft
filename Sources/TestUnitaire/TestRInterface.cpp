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
#include "TestRInterface.h"

/**
 * @brief Initializes a portfolio for the tests.
 */
TestRInterface::TestRInterface() {
	QString assetFolder = "../Examples/";

	// FIRST ASSET DEFINITION
	QDate startDate(2014, 1, 2);
	QDate endDate(2014, 3, 11);
	Asset* asset1 = new Asset("asset1", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QList<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
}

/**
 * @brief Tests the method checkCorrelation that computes the correlation of portfolio returns
 * in normal cases.
 */
void TestRInterface::testCheckCorrelation() {
	int timeLag, period;
	QDate date = this->father.retrieveEndDate();
	QPair<double, double> result;

	// Normal cases
	// Comparing results to a separate R execution
	timeLag = 1;
	period = 10;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {
		QFAIL("checkCorrelation failed at computing a valid parameters test");
	}
	// The toDouble() method in checkCorrelation seems to slightly
	// modify the precision, that is why the following test is performed
	QCOMPARE(result.first, 2.633048);
	QCOMPARE(result.second, 0.1046607);

	timeLag = 3;
	period = 20;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {
		QFAIL("checkCorrelation failed at computing a valid parameters test");
	}
	// The toDouble() method in checkCorrelation seems to slightly
	// modify the precision, that is why the following test is performed
	QCOMPARE(result.first, 6.277748);
	QCOMPARE(result.second, 0.09885197);
}

/**
 * @brief Tests the method checkCorrelation that computes the correlation of portfolio returns
 * with an incorrect time lag parameter
 */
void TestRInterface::testCheckCorrelationIncorrectTimeLag() {
	QPair<double, double> result;
	QDate date = this->father.retrieveEndDate();
	int timeLag = -1;
	int period = 10;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkCorrelation should have not executed");
	} catch(std::invalid_argument& e) {}
}

/**
 * @brief Tests the method checkCorrelation that computes the correlation of portfolio returns
 * with an incorrect period parameter
 */
void TestRInterface::testCheckCorrelationIncorrectPeriod() {
	QPair<double, double> result;
	QDate date = this->father.retrieveEndDate();
	int timeLag = 1;
	int period = -1;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkCorrelation should have not successfully executed");
	} catch(std::invalid_argument& e) {}
}

/**
 * @brief Tests the method checkCorrelation that computes the correlation of portfolio returns
 * with incompatibles time lag and period parameters
 */
void TestRInterface::testCheckCorrelationIncompatibleParameters() {
	QPair<double, double> result;
	QDate date = this->father.retrieveEndDate();
	int timeLag = 9;
	int period = 10;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkCorrelation should have not executed");
	} catch(std::invalid_argument& e) {}
}

/**
 * @brief Tests the method checkSquareCorrelation that computes the square correlation of portfolio returns
 * in normal cases
 */
void TestRInterface::testCheckSquareCorrelation() {
	int timeLag, period;
	QDate date = this->father.retrieveEndDate();
	QPair<double, double> result;

	// Normal cases
	timeLag = 1;
	period = 10;
	try {
		result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {
		QFAIL("checkSquareCorrelation failed at computing a valid parameters test");
	}
	QCOMPARE(result.first, 0.3349454);
	QCOMPARE(result.second, 0.5627615);

	timeLag = 3;
	period = 20;
	try {
		result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {
		QFAIL("checkSquareCorrelation failed at computing a valid parameters test");
	}
	QCOMPARE(result.first, 2.762662);
	QCOMPARE(result.second, 0.4296833);
}

/**
 * @brief Tests the method checkSquareCorrelation that computes the square correlation of portfolio returns
 * with incompatibles time lag and period parameters
 */
void TestRInterface::testCheckSquareCorrelationIncompatibleParameters() {
	QPair<double, double> result;
	QDate date = this->father.retrieveEndDate();
	int timeLag = 10;
	int period = 10;
	try {
		result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkSquareCorrelation should have not successfully executed");
	} catch(std::invalid_argument& e) {}
}
