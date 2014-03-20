#include "TestAsset.h"

/**
 * @brief Initializes an asset for the tests.
 */
TestAsset::TestAsset() {
	QDateTime firstDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime lastDate(QDate(2014, 1, 5), QTime(0, 0, 0));
	this->google = Asset("Google", "../../CSV_examples/asset1.txt", "YAHOO", firstDate, lastDate);
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
 * @brief Tests the method getValues that retrieves all values of an asset.
 */
void TestAsset::testRetrieveValues() {
	qDebug() << "Current dir: " << QDir::currentPath();

	QVector<double> result;

	// retrieveValues() version with dates parameters
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

	// retrieveValues() version without dates parameters
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

	QMap<QDateTime, double> result2;

	try {
		result2 = this->google.retrieveValuesByDate(this->google.getFirstDate(), this->google.getLastDate());
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QMapIterator<QDateTime, double> i(result2);
	while (i.hasNext()) {
		i.next();
		qDebug() << i.key().toString() << ": " << i.value() << endl;
	}

	// NONEXISTING FILE CASE
	try {
		result = this->missing.retrieveValues(this->missing.getFirstDate(), this->missing.getLastDate());
		QFAIL("retrieveValues() was able to open the file that should not exist");
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	// INCORRECT PARAMETERS CASE
	// firstDate is after endDate
	try {
		result = this->google.retrieveValues(this->google.getLastDate(), this->google.getFirstDate());
		QFAIL("retrieveValues was able to execute with incorrect date paramaeters");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}
}
