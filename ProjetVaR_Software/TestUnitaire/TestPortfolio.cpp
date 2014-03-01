#include "TestPortfolio.h"

/**
 * @brief Initializes a few portfolio for the tests.
 */
TestPortfolio::TestPortfolio() {
	QMap<Asset*, int> assets;
    QVector<Report*> reports;
	this->father = Portfolio("Test", assets, reports);
	this->son = Portfolio(&this->father, "Test", assets, reports);
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestPortfolio::testId() {
	QCOMPARE(this->father.getId(), -1);
	QCOMPARE(this->son.getParentId(), -1);
	this->father.setId(42);
	QCOMPARE(this->father.getId(), 42);
	QCOMPARE(this->son.getParentId(), 42);
	try {
		this->father.setId(43);
	} catch(const IdAlreadyAttributedException e) {
		return;
	}
	QFAIL("No exception thrown when attributed an id to a porfolio twice.");
}

/**
 * @brief Checks that the name can actually be changed.
 */
void TestPortfolio::testName() {
	QVERIFY(this->father.getName() == "Test");
	this->father.changeName("John");
	QVERIFY(this->father.getName() == "John");
}
