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

TestVaRHistorical::TestVaRHistorical()
{
}

void TestVaRHistorical::testExecute() {

    QString assetFolder = "../../CSV_examples/";

	// ASSET DEFINITION
	QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset dax("dax", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

    // TEST PORTFOLIO DEFINITION
    QMap<Asset*, int> assets;
	assets.insert(&dax, 1);
	QVector<Report*> reports;
	Portfolio daxPortfolio("daxPortfolio", assets, reports);

	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 20;
	VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);

	double var;

	try {
		var = daxVaR.execute(endDate);
	} catch(PortfolioCalculationException& e) {
		qDebug() << e.what();
	}

	qDebug() << "At the following date: " + endDate.toString();
	qDebug() << "For the asset: " + dax.getName();
	qDebug() << "Historical VaR parameters: risk=" << risk << ", timeHorizon=" << timeHorizon << "returnsPeriod=" << returnsPeriod;
	qDebug() << "Value-at-Risk=" << var;
}
