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
	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDate startDate(2014, 1, 2);
	QDate endDate(2014, 3, 11);
	Asset* asset1 = new Asset("asset1", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QVector<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
}

/**
 * @brief Tests the method checkCorrelation that computes the correlation of portfolio returns.
 */
void TestRInterface::testCheckCorrelation() {

	int timeLag, period;
	QDate date = this->father.retrieveEndDate();
	QPair<double, double> result;

	// Incorrect timeLag case
	timeLag = -1;
	period = 10;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkCorrelation should have not executed");
	} catch(std::invalid_argument& e) {}

	// Incorrect period case
	timeLag = 1;
	period = -1;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkCorrelation should have not successfully executed");
	} catch(std::invalid_argument& e) {}

	// Incompatible timeLag and period case
	timeLag = 9;
	period = 10;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkCorrelation should have not executed");
	} catch(std::invalid_argument& e) {}

	// Normal cases
	// Comparing results to a separate R execution
	timeLag = 1;
	period = 10;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {}
	// The toDouble() method in checkCorrelation seems to slightly
	// modify the precision, that is why the following test is performed
	QCOMPARE(QString::number(result.first), QString("2.51273"));
	QCOMPARE(QString::number(result.second), QString("0.11293"));

	timeLag = 3;
	period = 20;
	try {
		result = RInterface::checkCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {	}
	// The toDouble() method in checkCorrelation seems to slightly
	// modify the precision, that is why the following test is performed
	QCOMPARE(QString::number(result.first), QString("6.44423"));
	QCOMPARE(QString::number(result.second), QString("0.0918881"));
}

/**
 * @brief Tests the method checkSquareCorrelation that computes the square correlation of portfolio returns.
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
	} catch(std::invalid_argument& e) {}
	QCOMPARE(QString::number(result.first), QString("0.343539"));
	QCOMPARE(QString::number(result.second), QString("0.557793"));

	timeLag = 3;
	period = 20;
	try {
		result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
	} catch(std::invalid_argument& e) {}
	QCOMPARE(QString::number(result.first), QString("2.77258"));
	QCOMPARE(QString::number(result.second), QString("0.428033"));

	// Incompatible parameters case
	timeLag = 10;
	period = 10;
	try {
		result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
		QFAIL("RInterface::checkSquareCorrelation should have not successfully executed");
	} catch(std::invalid_argument& e) {}

}