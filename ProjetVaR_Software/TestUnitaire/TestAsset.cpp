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
	QDateTime firstDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime lastDate(QDate(2014, 1, 5), QTime(0, 0, 0));
	this->google = Asset("Google", "../../CSV_examples/asset1.txt", "YAHOO", firstDate, lastDate);
	this->apple = Asset("Apple", "../../CSV_examples/asset4.txt", "YAHOO", QDateTime(QDate(2014, 1, 1), QTime(0, 0, 0)),
						QDateTime(QDate(2014, 1, 4), QTime(0, 0, 0)));
	this->missing = Asset("test", "../../CSV_examples/nonexistingfile.txt", "YAHOO", firstDate, lastDate);
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
 * @brief Tests the method retrieveValues that retrieves all values of an asset.
 */
void TestAsset::testRetrieveValues() {

	qDebug() << "Current dir: " << QDir::currentPath();

	QVector<double> result;

	// DATE PARAMETERS FUNCTION TESTS:
	// QVector<double> Asset::RetrieveValues(const QDateTime& startDate, const QDateTime& endDate) const
	try {
		result = this->google.retrieveValues(this->google.getFirstDate(), this->google.getLastDate());
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
	QCOMPARE(result.at(2), 103.0);
	QCOMPARE(result.at(3), 104.0);

	// INCORRECT DATE PARAMETERS CASE
	// firstDate is after endDate
	try {
		result = this->google.retrieveValues(this->google.getLastDate(), this->google.getFirstDate());
		QFAIL("retrieveValues was able to execute with incorrect date paramaters");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}

	// NONEXISTING FILE CASE
	try {
		result = this->missing.retrieveValues(this->missing.getFirstDate(), this->missing.getLastDate());
		QFAIL("retrieveValuesByDate() was able to open a file that should not exist");
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	// SPECIAL DATE PARAMETERS CASE
	// The first date can be older than the actual oldest date in the file.
	// The returned vector will simply start with the actual oldest date.
	// The same goes with the last date in its opposite way.
	QDateTime firstDate(QDate(2013, 12, 25), QTime(0, 0, 0));
	QDateTime lastDate(QDate(2014, 1, 10), QTime(0, 0, 0));
	try {
		result = this->google.retrieveValues(firstDate, lastDate);
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 6);
	QCOMPARE(result.at(0), 100.0);
	QCOMPARE(result.at(1), 101.0);
	QCOMPARE(result.at(2), 102.0);
	QCOMPARE(result.at(3), 103.0);
	QCOMPARE(result.at(4), 104.0);
	QCOMPARE(result.at(5), 105.0);

	// UNAVAILABLE DATES IN THE MIDDLE CASE
	try {
		result = this->apple.retrieveValues(QDateTime(QDate(2014, 1, 3), QTime(0, 0, 0)),
											QDateTime(QDate(2014, 1, 3), QTime(0, 0, 0)));
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QVERIFY(result.isEmpty());

	// NO PARAMETER FUNCTION TESTS:
	// QVector<double> Asset::RetrieveValues() const

	try {
		result = this->google.retrieveValues();
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
	QCOMPARE(result.at(2), 103.0);
	QCOMPARE(result.at(3), 104.0);
}

/**
 * @brief Tests the method retrieveValuesByDate that retrieves all date-values of an asset.
 */
void TestAsset::testRetrieveValuesByDate() {
	QMap<QDateTime, double> result;


	// EXPECTED AND SUCCESSFUL CASE
	try {
		result = this->google.retrieveValuesByDate(this->google.getFirstDate(), this->google.getLastDate());
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 2), QTime(0, 0, 0))), 101.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 3), QTime(0, 0, 0))), 102.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 4), QTime(0, 0, 0))), 103.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 5), QTime(0, 0, 0))), 104.0);

	// INCORRECT DATE PARAMETERS CASE
	// firstDate is after endDate
	try {
		result = this->google.retrieveValuesByDate(this->google.getLastDate(), this->google.getFirstDate());
		QFAIL("retrieveValuesByDate was able to execute with incorrect date paramaters");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}

	// NONEXISTING FILE CASE
	try {
		result = this->missing.retrieveValuesByDate(this->missing.getFirstDate(), this->missing.getLastDate());
		QFAIL("retrieveValuesByDate() was able to open a file that should not exist");
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	// SPECIAL DATE PARAMETERS CASE
	// The first date can be older than the actual oldest date in the file.
	// The returned map will simply start with the actual oldest date.
	// The same goes with the last date in its opposite way.
	QDateTime firstDate(QDate(2013, 12, 25), QTime(0, 0, 0));
	QDateTime lastDate(QDate(2014, 1, 10), QTime(0, 0, 0));
	try {
		result = this->google.retrieveValuesByDate(firstDate, lastDate);
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 6);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 1), QTime(0, 0, 0))), 100.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 2), QTime(0, 0, 0))), 101.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 3), QTime(0, 0, 0))), 102.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 4), QTime(0, 0, 0))), 103.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 5), QTime(0, 0, 0))), 104.0);
	QCOMPARE(result.value(QDateTime(QDate(2014, 1, 6), QTime(0, 0, 0))), 105.0);
}
