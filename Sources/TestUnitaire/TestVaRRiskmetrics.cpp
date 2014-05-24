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
#include "TestVaRRiskmetrics.h"

/**
 * @brief Initializes a portfolio to perform VaR computation
 */
TestVaRRiskmetrics::TestVaRRiskmetrics() {
	QString assetFolder = "../../Examples/";

	// ASSET DEFINITION
	QDate startDate(QDate(2014, 1, 2));
	QDate endDate(QDate(2014, 3, 11));
	Asset* dax = new Asset("dax", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(dax, 1);
	QList<Report*> reports;
	this->daxPortfolio = Portfolio("daxPortfolio", assets, reports);
}

/**
 * @brief Checks that VaRRiskmetrics object cannot be created with incorrect initPeriod value
 */
void TestVaRRiskmetrics::testConstructor() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 3;
	int initPeriod = 0;

	try {
		VaRRiskmetrics riskMetricsAlgo(this->daxPortfolio, risk, timeHorizon, initPeriod);
		QFAIL("VaRRiskmetrics constructor should have failed given the incorrect initPeriod");
	} catch(std::invalid_argument& e) {}
}

/**
 * @brief Performs a correct VaR computation according to the RiskMetrics method
 */
void TestVaRRiskmetrics::testExecuteCorrect1() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int initPeriod = 20;
	VaRRiskmetrics riskMetricsAlgo(this->daxPortfolio, risk, timeHorizon, initPeriod);

	double var = riskMetricsAlgo.execute(QDate(2014, 3, 12));
	QCOMPARE(var, 165.7452256572);
}

/**
 * @brief Performs an other correct VaR computation according to the RiskMetrics method with
 * a multiple days time horizon
 */
void TestVaRRiskmetrics::testExecuteCorrect2() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 3;
	int initPeriod = 20;
	VaRRiskmetrics riskMetricsAlgo(this->daxPortfolio, risk, timeHorizon, initPeriod);

	double var = riskMetricsAlgo.execute(QDate(2014, 3, 12));
	QCOMPARE(var, 287.0791519502);
}
