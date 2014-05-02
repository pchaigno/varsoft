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
	QDate startDate1(2014, 1, 2);
	QDate endDate1(2014, 3, 11);
	Asset* asset1 = new Asset("asset1", assetFolder+"dax.csv", "YAHOO", startDate1, endDate1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QVector<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
}

void TestRInterface::testComputeGarchModel() {
	int period = 10;
	GarchModel model = RInterface::computeGarchModel(this->father, this->father.retrieveEndDate(), period);

	QCOMPARE(model.getOmega(), 0.0002504062);
	QCOMPARE(model.getAlpha(), 0.0500141719);
	QCOMPARE(model.getBeta(), 0.0499956054);
	QCOMPARE(model.getResiduals().size(), 9);
	QCOMPARE(model.getResiduals().at(0), -0.468397283);
	QCOMPARE(model.getResiduals().at(1), 0.659176463);
	QCOMPARE(model.getResiduals().at(2), -2.130830688);
	QCOMPARE(model.getResiduals().at(3), 1.348051460);
	QCOMPARE(model.getResiduals().at(4), -0.286279545);
	QCOMPARE(model.getResiduals().at(5), 0.005457179);
	QCOMPARE(model.getResiduals().at(6), -1.252346813);
	QCOMPARE(model.getResiduals().at(7), -0.543204489);
	QCOMPARE(model.getResiduals().at(8), 0.277749688);
	QCOMPARE(model.getStddev(), 0.01639555);
}

void TestRInterface::testComputeGarchModelIncorrectParameter() {
	int period = 2;
	try {
		GarchModel model = RInterface::computeGarchModel(this->father, this->father.retrieveEndDate(), period);
		QFAIL("computeGarchModel() should not have succeeded in computing a Garch model");
	} catch(std::invalid_argument& e) {

	}

}
