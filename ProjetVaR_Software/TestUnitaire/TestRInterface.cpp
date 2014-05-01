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

void TestRInterface::testComputeGarchModel() {

	int period = 5;
	qDebug() << this->father.retrieveLogReturns(this->father.retrieveEndDate(), period);
	GarchModel model = RInterface::computeGarchModel(this->father, this->father.retrieveEndDate(), period);

//	QCOMPARE(QString::number(model.getOmega()), QString("0.000250406"));
//	QCOMPARE(testModel.getAlpha(), );
//	QCOMPARE(testModel.getBeta(), );

	qDebug() << "omega=" << model.getOmega();
	qDebug() << "alpha=" << model.getAlpha();
	qDebug() << "beta=" << model.getBeta();
	qDebug() << "residuals=" << model.getResiduals();
	qDebug() << "stddev=" << model.getStddev();

//	qDebug() << QString::number(testModel.getOmega(), 'g', 1000);
//	qDebug() << QString::number(testModel.getAlpha(), 'g', 1000);
//	qDebug() << QString::number(testModel.getBeta(), 'g', 1000);

}
