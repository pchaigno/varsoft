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
#include "TestBacktesting.h"

/**
 * @brief TestBacktesting::TestBacktesting
 */
TestBacktesting::TestBacktesting() {
	QString assetFolder = "../../CSV_examples/";

	// ASSET DEFINITION
	QDate startDate(QDate(1990, 3, 2));
	QDate endDate(QDate(2014, 5, 19));
	Asset* cac40 = new Asset("CAC40", assetFolder+"cac40.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(cac40, 1);
	QList<Report*> reports;
	this->portfolio = Portfolio("daxPortfolio", assets, reports);
}

void TestBacktesting::testCompute() {
	double risk = 0.01;
	int timeHorizon = 1;
	int returnsPeriod = 50;
	VaRHistorical varAlgo(this->portfolio, risk, timeHorizon, returnsPeriod);
	QPair<QDate, QDate> interval;
	interval.first = QDate(2013, 1, 2);
	interval.second = QDate(2013, 12, 31);
	Backtesting backtest(this->portfolio, varAlgo, interval);
	QCOMPARE(backtest.compute(), 4);
}