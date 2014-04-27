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

/**
* @brief Initializes an asset for the tests.
*/
TestImportNewData::TestImportNewData() {
    TestImportNewData::startDate = "2014-01-01";
    TestImportNewData::endDate = "2014-02-01";
    Asset b = Asset("Gogolea","../../CSV_examples/Gogolea_test.csv","Yahoo",QDate::fromString(TestImportNewData::startDate,"yyyy-MM-dd"), QDate::fromString(TestImportNewData::endDate,"yyyy-MM-dd"));
    ImportNewData algo = ImportNewData();
    algo.import(b,"../../CSV_examples/table.csv");
    SessionSaver::getInstance()->saveAsset(b);

    QString data;
    QFile importedCSV("../../CSV_examples/Gogolea_test.csv");
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

    for (int x =1; x < rowOfData.size()-1; x++)	{
        rowData = rowOfData.at(x).split(",");
        qDebug() << rowData[0] << "," << rowData[1];
    }
    Asset *a = SessionBuilder::getInstance()->buildAsset("Gogolea");

    QVERIFY(a->getFile() == "../../CSV_examples/Gogolea_test.csv");
    QVERIFY(a->getStartDate() == QDate::fromString(TestImportNewData::startDate, "yyyy-MM-dd"));
    QVERIFY(a->getEndDate() == QDate::fromString(TestImportNewData::endDate, "yyyy-MM-dd"));
    QVERIFY(a->getName() == "Gogolea");
    QVERIFY(a->getOrigin() == "Yahoo");
    QVERIFY((AssetsFactory::getInstance()->retrieveAsset("Gogolea") != NULL) == true);
    // Deletes the database file:
    QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
    databaseFile.remove();
}

/**
 * @brief Checks that the startDate and the endDate of the generated file correspond to the params
 */
void TestImportNewData::testDates() {
    QString data;
    QFile importedCSV("../../CSV_examples/Gogolea_test.csv");
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
 *	Test the regexp for dates and values
 **/
void TestImportNewData::testRegexp() {
    QRegExp date_regex("^(20|19)[0-9]{2}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$");
    QRegExp value_regex("^([0-9]+)([.])([0-9][0-9])$");
    QVERIFY(date_regex.exactMatch("2014-10-10") == true);
    QVERIFY(value_regex.exactMatch("24.15") == true);
    QVERIFY(date_regex.exactMatch("10-10-2014") == false);
    QVERIFY(value_regex.exactMatch("2z.zd") == false);
}

/**
 *	Checks the unicity of names
 **/
void TestImportNewData::testUnicityName() {
    //QVERIFY((AssetsFactory::getInstance()->retrieveAsset("Gogole") != NULL) == true);
    QVERIFY((AssetsFactory::getInstance()->retrieveAsset("Gogoleaa") != NULL) == false);
}
