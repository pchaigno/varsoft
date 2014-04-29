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
#include "TestAsset.h"

/**
 * @brief Initializes an asset for the tests.
 */
TestAsset::TestAsset() {
	QDate startDate(2014, 1, 2);
	QDate endDate(2014, 1, 5);
	this->google = Asset("Google", "../../CSV_examples/asset1.txt", "YAHOO", startDate, endDate);
	this->apple = Asset("Apple", "../../CSV_examples/asset4.txt", "YAHOO", QDate(2013, 12, 30), QDate(2014, 1, 2));
	this->missing = Asset("test", "../../CSV_examples/nonexistingfile.txt", "YAHOO", startDate, endDate);
	this->asset1 = Asset("Asset1", "../../CSV_examples/asset1.txt", "YAHOO", QDate(2014, 01, 01), QDate(2014, 01, 06));
	this->weekends = Asset("Weekends", "../../CSV_examples/asset6.txt", "ProjectVaR", QDate(2014, 01, 5), QDate(2014, 01, 26));
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestAsset::testId() {
	QCOMPARE(this->google.getId(), -1);
	this->google.setId(42);
	QCOMPARE(this->google.getId(), 42);
	try {
		this->google.setId(43);
	} catch(const IdAlreadyAttributedException e) {
		return;
	}
	QFAIL("No exception thrown when attributed an id to an asset twice.");
}

/**
 * @brief Checks that the name can actually be changed.
 */
void TestAsset::testName() {
	QVERIFY(this->google.getName() == "Google");
	this->google.changeName("Googl");
	QVERIFY(this->google.getName() == "Googl");
}

/**
 * @brief Successful test on retrieveValues.
 * The definition period of the asset contains a weekend.
 */
void TestAsset::testRetrieveValuesWeekend() {
	QVector<double> result = this->asset1.retrieveValues(QDate(2014, 1, 3), QDate(2014, 1, 6));
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.at(0), 102.0);
	QCOMPARE(result.at(1), 105.0);
}

/**
 * @brief Successful test on retrieveValues.
 * The definition period of the asset is only defined on weekends.
 */
void TestAsset::testRetrieveValuesWeekends() {
	QVector<double> result = this->weekends.retrieveValues();
	QCOMPARE(result.size(), 15);
}

/**
 * @brief Successful test on retrieveValues.
 */
void TestAsset::testRetrieveValues() {
	QVector<double> result = this->google.retrieveValues(QDate(2014, 1, 3), QDate(2014, 1, 5));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 102.0);
}

/**
 * @brief Checks that the retrieveValues throws an exception
 * if the dates are inversed.
 */
void TestAsset::testRetrieveValuesIncorrectDates() {
	try {
		QVector<double> result = this->google.retrieveValues(this->google.getEndDate(), this->google.getStartDate());
		QFAIL("retrieveValues was able to execute with incorrect date paramaters");
	} catch(std::exception& e) {

	}
}

/**
 * @brief Checks that retrieveValues throws an exception
 * if the file with the values doesn't exist.
 */
void TestAsset::testRetrieveValuesNonexistingFile() {
	try {
		QVector<double> result = this->missing.retrieveValues(this->missing.getStartDate(), this->missing.getEndDate());
		QFAIL("retrieveValuesByDate() was able to open a file that should not exist");
	} catch(CannotOpenFileException& e) {

	}
}

/**
 * @brief Test a special date parameters case.
 * The first date can be older than the actual oldest date in the file.
 * The returned vector will simply start with the actual oldest date.
 * The same goes with the last date in its opposite way.
 */
void TestAsset::testRetrieveValuesSpecialDates() {
	QVector<double> result = this->google.retrieveValues(QDate(2013, 12, 25), QDate(2014, 1, 10));
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
}

/**
 * @brief Tries to retrieveValues for a day unavailable between the dates of definition.
 * The value of the preceding day should be returned.
 */
void TestAsset::testRetrieveValuesUnavailableDates() {
	QVector<double> result = this->apple.retrieveValues(QDate(2013, 12, 31), QDate(2013, 12, 31));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 98.0);
}

/**
 * @brief Successful test on the retrieveValues without parameters.
 */
void TestAsset::testRetrieveValuesNoParameters() {
	QVector<double> result = this->google.retrieveValues();
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
}

/**
 * @brief Successful test on retrieveValuesByDate.
 * The definition period of the asset contains a weekend.
 */
void TestAsset::testRetrieveValuesByDateWeekend() {
	QMap<QDate, double> result = this->asset1.retrieveValuesByDate(QDate(2014, 1, 3), QDate(2014, 1, 6));
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.value(QDate(2014, 01, 03)), 102.0);
	QCOMPARE(result.value(QDate(2014, 01, 06)), 105.0);
}

/**
 * @brief Tests the method retrieveValuesByDate that retrieves all date-values of an asset.
 * Successful test
 */
void TestAsset::testRetrieveValuesByDate() {
	QMap<QDate, double> result = this->google.retrieveValuesByDate(QDate(2014, 1, 3), QDate(2014, 1, 5));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.value(QDate(2014, 1, 3)), 102.0);
}

/**
 * @brief Checks that the retrieveValuesByDate throws an exception
 * if the dates are in inversed.
 */
void TestAsset::testRetrieveValuesByDateIncorrectDates() {
	try {
		QMap<QDate, double> result = this->google.retrieveValuesByDate(this->google.getEndDate(), this->google.getStartDate());
		QFAIL("retrieveValuesByDate was able to execute with incorrect date paramaters");
	} catch(std::exception& e) {

	}
}

/**
 * @brief Checks that retrieveValuesByDate throws an exception
 * if the file with the values doesn't exist.
 */
void TestAsset::testRetrieveValuesByDateNonexistingFile() {
	try {
		QMap<QDate, double> result = this->missing.retrieveValuesByDate(this->missing.getStartDate(), this->missing.getEndDate());
		QFAIL("retrieveValuesByDate() was able to open a file that should not exist");
	} catch(CannotOpenFileException& e) {

	}
}

/**
 * Test a special date parameters case.
 * The first date can be older than the actual oldest date in the file.
 * The returned vector will simply start with the actual oldest date.
 * The same goes with the last date in its opposite way.
 */
void TestAsset::testRetrieveValuesByDateSpecialDates() {
	QMap<QDate, double> result = this->google.retrieveValuesByDate(QDate(2013, 12, 25), QDate(2014, 1, 10));
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.value(QDate(2014, 1, 2)), 101.0);
	QCOMPARE(result.value(QDate(2014, 1, 3)), 102.0);
}

/**
 * @brief Tries to retrieveValuesByDate for a day unavailable between the dates of definition.
 * The value of the preceding day should be returned.
 */
void TestAsset::testRetrieveValuesByDateUnavailableDates() {
	QMap<QDate, double> result = this->apple.retrieveValuesByDate(QDate(2013, 12, 31), QDate(2013, 12, 31));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.value(QDate(2013, 12, 31)), 98.0);
}
