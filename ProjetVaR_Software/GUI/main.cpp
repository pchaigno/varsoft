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
#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "import.h"

#include "RInterface.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	QString assetFolder = "../../CSV_examples/";

	// FIRST ASSET DEFINITION
	QDateTime startDate1(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime endDate1(QDate(2014, 3, 11), QTime(0, 0, 0));
	Asset* asset1 = new Asset("asset1", assetFolder+"dax.csv", "YAHOO", startDate1, endDate1);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	QVector<Report*> reports;
	Portfolio father("Father", assets, reports);

	int timeLag = 1;
	QDateTime date = father.retrieveEndDate();
	int period = 5;

	qDebug() << father.retrieveReturns(father.retrieveEndDate(), period);

	QPair<double, double> result = RInterface::checkCorrelation(father, timeLag, date, period);

	qDebug() << result.first;
	qDebug() << result.second;


	MainWindow w;
	w.showMaximized();
	return a.exec();
}
