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
#include "TestCreateAsset.h"
#include <QDebug>

/**
* @brief Tests import of ImportNewData.
*/
void TestCreateAsset::testImport() {
	QDate startDate = QDate::fromString("2014-01-01", "yyyy-MM-dd");
	QDate endDate = QDate::fromString("2014-02-01", "yyyy-MM-dd");
	Asset b = Asset("Gogolea", "../../CSV_examples/Gogolea_test.csv", "Yahoo", startDate, endDate);
	CreateAsset algo = CreateAsset();
	algo.import(b, "../../CSV_examples/table.csv");
	SessionSaver::getInstance()->saveAsset(b);

	QString data;
	QFile importedCSV("../../CSV_examples/Gogolea_test.csv");
	QStringList dataRows;
	QStringList dataRow;

	if (importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		dataRows = data.split("\n");
		importedCSV.close();
	}
	QCOMPARE(dataRows.size(), 23);
	// Checks first date:
	dataRow = dataRows.at(1).split(",");
	QVERIFY(endDate >= QDate::fromString(dataRow[0], "yyyy-MM-dd"));
	// Checks last date:
	dataRow = dataRows.at(dataRows.size()-2).split(",");
	QVERIFY(startDate <= QDate::fromString(dataRow[0], "yyyy-MM-dd"));

	Asset *a = SessionBuilder::getInstance()->buildAsset("Gogolea");
	QVERIFY(a->getFile() == "../../Examples/Gogolea_test.csv");
	QVERIFY(a->getStartDate() == startDate);
	QVERIFY(a->getEndDate() == endDate);
	QVERIFY(a->getName() == "Gogolea");
	QVERIFY(a->getOrigin() == "Yahoo");
	QVERIFY(AssetsFactory::getInstance()->retrieveAsset("Gogolea") != NULL);

	//Verify the day of week
	int size = dataRows.size();
	for (int x =1; x < size; x++) {
		dataRow = dataRows.at(x).split(",");
		QVERIFY((QDate::fromString(dataRow[0], "yyyy-MM-dd").dayOfWeek() <= 5));
	}
	// Deletes the database file:
	QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
	databaseFile.remove();
}


