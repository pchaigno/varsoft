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
void TestAsset::testGetValues() {
	qDebug() << "Current dir: " << QDir::currentPath();

	QVector<double> result;

	try {
		result = this->google.getValues(this->google.getFirstDate(), this->google.getLastDate());
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
	QCOMPARE(result.at(2), 103.0);
	QCOMPARE(result.at(3), 104.0);

	// NONEXISTING FILE CASE FOR ILLUSTRATION PURPOSES
	try {
		result = this->missing.getValues(this->missing.getFirstDate(), this->missing.getLastDate());
		QFAIL("getValues() was able to open the file that should not exist");
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}
}
