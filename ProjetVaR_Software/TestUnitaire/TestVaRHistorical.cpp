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

#include "TestVaRHistorical.h"

TestVaRHistorical::TestVaRHistorical() {
	QString assetFolder = "../../CSV_examples/";

	// ASSET DEFINITION
	QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset* dax = new Asset("dax", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(dax, 1);
	QVector<Report*> reports;
	this->daxPortfolio = Portfolio("daxPortfolio", assets, reports);
}

void TestVaRHistorical::testVaRHistoricalConstructor() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 0; // INTENDED INCORRECT VALUE

	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong returnsPeriod parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	// ANOTHER IMPOSSIBLE CASE
	returnsPeriod = -3;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong returnsPeriod parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}
}

void TestVaRHistorical::testExecute() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 20;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	double var;

	try {
		var = daxVaR.execute(this->daxPortfolio.retrieveLastDate());
		qDebug() << "At the following date: " + this->daxPortfolio.retrieveLastDate().toString();
		qDebug() << "For the asset: " + this->daxPortfolio.getName();
		qDebug() << "Historical VaR parameters: risk=" << risk << ", timeHorizon=" << timeHorizon << "returnsPeriod=" << returnsPeriod;
		qDebug() << "Value-at-Risk=" << var;
	} catch(std::range_error& e) {
		qDebug() << e.what();
	}

	// TOO LARGE returnsPeriod CASE
	returnsPeriod = 100;
	VaRHistorical incorrectDaxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);
	try {
		var = incorrectDaxVaR.execute(this->daxPortfolio.retrieveLastDate());
		QFAIL("execute() succeeded despite too large returnsPeriod parameter");

	} catch(std::range_error& e) {
		qDebug() << e.what();
	}
}
