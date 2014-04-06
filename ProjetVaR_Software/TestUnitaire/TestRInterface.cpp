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
	QDateTime startDate1(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate1(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset* asset1 = new Asset("asset1", assetFolder+"dax.csv", "YAHOO", startDate1, endDate1);

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

	int timeLag = 1;
	QDateTime date = this->father.retrieveEndDate();
	int period = 5;

	qDebug() << this->father.retrieveReturns(this->father.retrieveEndDate(), period);

	QPair<double, double> result = RInterface::checkCorrelation(this->father, timeLag, date, period);
	// Comparing results coming from a classic R execution
	// Info: qDebug does not print all the digits. It may be confusing when debugging
//	QCOMPARE(result.first, 0.3762625);
//	QCOMPARE(result.second, 0.5396103);

	// Testing the timeLag parameter
	timeLag = 2;
	result = RInterface::checkCorrelation(this->father, timeLag, date, period);
//	QCOMPARE(result.first, 0.5352686);
//	QCOMPARE(result.second, 0.7651876);

}

/**
 * @brief Tests the method checkSquareCorrelation that computes the square correlation of portfolio returns.
 */
void TestRInterface::testCheckSquareCorrelation() {
	int timeLag = 1;
	QDateTime date = this->father.retrieveEndDate();
	int period = 5;

	QPair<double, double> result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
	// Comparing results coming from a classic R execution
	// Info: qDebug does not print all the digits. It may be confusing when debugging
	QCOMPARE(result.first, 0.5362667);
	QCOMPARE(result.second, 0.4639841);

	// Testing the timeLag parameter
	timeLag = 2;
	result = RInterface::checkSquareCorrelation(this->father, timeLag, date, period);
	QCOMPARE(result.first, 2.500883);
	QCOMPARE(result.second, 0.2863783);
}
