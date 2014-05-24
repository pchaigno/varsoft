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
 * @brief Builds a portfolio made of the single CAC40 index asset
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
	this->portfolio = new Portfolio("daxPortfolio", assets, reports);
}

/**
 * @brief Performs a backtesting using the historical method
 */
void TestBacktesting::testBacktestingHistorical() {
	double risk = 0.01;
	int timeHorizon = 1;
	int returnsPeriod = 50;
	VaRHistorical varAlgo(*portfolio, risk, timeHorizon, returnsPeriod);
	QPair<QDate, QDate> interval;
	interval.first = QDate(2013, 1, 2);
	interval.second = QDate(2013, 12, 31);
	Backtesting backtest(*portfolio, varAlgo, interval);
	QCOMPARE(backtest.compute(), 4);
}

/**
 * @brief Performs a backtesting using the RiskMetrics method
 */
void TestBacktesting::testBacktestingRiskmetrics() {
	double risk = 0.05;
	int timeHorizon = 1;
	int initPeriod = 30;
	VaRRiskmetrics varAlgo(*portfolio, risk, timeHorizon, initPeriod);
	QPair<QDate, QDate> interval;
	interval.first = QDate(2014, 1, 1);
	interval.second = QDate(2014, 5, 19);
	Backtesting backtest(*portfolio, varAlgo, interval);
	QCOMPARE(backtest.compute(), 6);
}

/**
 * @brief Tests that the incorrect start date of the interval prevents
 * the backtesting from being executed
 */
void TestBacktesting::testBacktestingIncorrect1() {
	double risk = 0.05;
	int timeHorizon = 1;
	int initPeriod = 30;
	VaRRiskmetrics varAlgo(*portfolio, risk, timeHorizon, initPeriod);
	QPair<QDate, QDate> interval;
	interval.first = QDate(1990, 3, 2);
	interval.second = QDate(2013, 12, 31);
	try {
		Backtesting backtest(*portfolio, varAlgo, interval);
		QFAIL("The backtesting succeeded despite a wrong dates interval.");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests that the incorrect end date of the interval prevents
 * the backtesting from being executed
 */
void TestBacktesting::testBacktestingIncorrect2() {
	double risk = 0.05;
	int timeHorizon = 1;
	int initPeriod = 30;
	VaRRiskmetrics varAlgo(*portfolio, risk, timeHorizon, initPeriod);
	QPair<QDate, QDate> interval;
	interval.first = QDate(2013, 1, 1);
	interval.second = QDate(2014, 5, 20);
	try {
		Backtesting backtest(*portfolio, varAlgo, interval);
		QFAIL("The backtesting succeeded despite a wrong dates interval.");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests that incompatible time horizon and end date of the interval prevents
 * the backtesting from being executed
 */
void TestBacktesting::testBacktestingIncorrect3() {
	double risk = 0.05;
	int timeHorizon = 2;
	int initPeriod = 30;
	VaRRiskmetrics varAlgo(*portfolio, risk, timeHorizon, initPeriod);
	QPair<QDate, QDate> interval;
	interval.first = QDate(2013, 1, 1);
	interval.second = QDate(2014, 5, 19);
	try {
		Backtesting backtest(*portfolio, varAlgo, interval);
		QFAIL("The backtesting succeeded despite a wrong dates interval.");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}
}
