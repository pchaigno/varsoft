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
#include "TestImportNewData.h"
#include "SessionBuilder.h"
#include "SessionSaver.h"

/**
* @brief Initializes an asset for the tests.
*/
TestImportNewData::TestImportNewData() {
	TestImportNewData::stockName = "Gogole";
	TestImportNewData::startDate = "2014-02-07";
	TestImportNewData::endDate = "2014-01-01";
	TestImportNewData::origin = "Yahoo";
	QString data;
	QFile importedCSV("../../CSV_examples/table.csv");
	QStringList rowOfData;
	QStringList rowData;
	data.clear();
	rowOfData.clear();
	rowData.clear();

	if (importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		rowOfData = data.split("\n");
		importedCSV.close();
	}

	TestImportNewData::newFile = "../../CSV_examples/"+TestImportNewData::stockName+"_test.csv";
	QFile fileCreated(TestImportNewData::newFile);
	if (!fileCreated.open(QIODevice::WriteOnly | QIODevice::Text)) {
	   return;
	}
	QTextStream flux(&fileCreated);
	flux.setCodec("UTF-8");
	const QDateTime &fiDate = QDateTime::fromString(TestImportNewData::startDate,"yyyy-MM-dd");
	const QDateTime &laDate = QDateTime::fromString(TestImportNewData::endDate,"yyyy-MM-dd");
	for (int x =1; x < rowOfData.size()-1; x++)	{
		rowData = rowOfData.at(x).split(",");
		QDateTime currentDate = QDateTime::fromString(rowData[0],"yyyy-MM-dd");
		if ((fiDate >= currentDate)) {
			if(laDate >= currentDate) {
				break;
			}
			flux << rowData[0] << "," << rowData[6] << "\n";
		}
	}
	fileCreated.close();
	Asset a = Asset("Gogole",TestImportNewData::newFile,TestImportNewData::origin,fiDate,laDate);
	SessionSaver::getInstance()->saveAsset(a);
}

/**
 * @brief Checks that the startDate and the endDate of the generated file correspond to the params
 */
void TestImportNewData::testDates() {
	QString data;
	QFile importedCSV(TestImportNewData::newFile);
	QStringList rowOfData;
	QStringList rowData;
	data.clear();
	rowOfData.clear();
	rowData.clear();
	if (importedCSV.open(QFile::ReadOnly)) {
		data = importedCSV.readAll();
		rowOfData = data.split("\n");
		importedCSV.close();
	}
	//first date
	rowData = rowOfData.at(0).split(",");
	QVERIFY((QDateTime::fromString(TestImportNewData::startDate,"yyyy-MM-dd")) >= (QDateTime::fromString(rowData[0],"yyyy-MM-dd")));

	//last date
	rowData = rowOfData.at(rowOfData.size()-2).split(",");
	QVERIFY((QDateTime::fromString(TestImportNewData::endDate,"yyyy-MM-dd")) <= (QDateTime::fromString(rowData[0],"yyyy-MM-dd")));
}

/**
 * @brief Test the recording in the database at the importation.
 */
void TestImportNewData::testDB() {
	Asset *a = SessionBuilder::getInstance()->buildAsset("Gogole");
	QVERIFY(a->getFile() == TestImportNewData::newFile);
	QVERIFY(a->getStartDate() <= QDateTime::fromString(TestImportNewData::startDate,"yyyy-MM-dd"));
	QVERIFY(a->getEndDate() >= QDateTime::fromString(TestImportNewData::endDate,"yyyy-MM-dd"));
	QVERIFY(a->getName() == TestImportNewData::stockName);
	QVERIFY(a->getOrigin() == TestImportNewData::origin);

	// Deletes the database file:
	QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
	databaseFile.remove();
}
