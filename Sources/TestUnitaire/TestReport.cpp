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
#include "TestReport.h"

/**
 * @brief Initializes a few reports for the tests.
 */
TestReport::TestReport() {
	this->var = new VaRReport("somefolder/var");
	this->garch = new GarchReport("somefolder/garch");
	this->correlation = new CorrelationReport("somefolder/correlation");
	this->backtesting = new BacktestingReport("somefolder/backtesting");
	this->statistics = new StatisticsReport("somefolder/statistics");
}

TestReport::~TestReport() {
	delete var;
	delete garch;
	delete correlation;
	delete backtesting;
	delete statistics;
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestReport::testId() {
	this->testId(this->garch);
	this->testId(this->statistics);
	this->testId(this->backtesting);
	this->testId(this->var);
	this->testId(this->correlation);
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestReport::testId(Report *report) {
	QCOMPARE(report->getId(), -1);
	report->setId(42);
	QCOMPARE(report->getId(), 42);
	QVERIFY(report->isUpToDate());
	try {
		report->setId(43);
	} catch(const IdAlreadyAttributedException e) {
		return;
	}
	QFAIL("No exception thrown when attributed an id to a report twice.");
}

/**
 * @brief Compares a serialized/deserialized report with the original report.
 */
void TestReport::testSerialize() {
	// The report already has an ID.
	QJsonObject json = this->statistics->toJSON();
	StatisticsReport test(json);

	QCOMPARE(test.getId(), -1);
	QCOMPARE(test.getFile(), this->statistics->getFile());
	QCOMPARE(test.getType(), this->statistics->getType());
}
