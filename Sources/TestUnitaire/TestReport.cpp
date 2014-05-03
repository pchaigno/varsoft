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
	this->var = VaRReport("C:\\somefolder\\var.docx", "C:\\somefolder\\var.pdf");
	this->garch = GarchReport("C:\\somefolder\\garch.docx", "C:\\somefolder\\garch.pdf");
	this->correlation = CorrelationReport("C:\\somefolder\\correlation.docx", "C:\\somefolder\\correlation.pdf");
	this->backtesting = BacktestingReport("C:\\somefolder\\backtesting.docx", "C:\\somefolder\\backtesting.pdf");
	this->statistics = StatisticsReport("C:\\somefolder\\statistics.docx", "C:\\somefolder\\statistics.pdf");
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
void TestReport::testId(Report report) {
	QCOMPARE(report.getId(), -1);
	report.setId(42);
	QCOMPARE(report.getId(), 42);
	try {
		report.setId(43);
	} catch(const IdAlreadyAttributedException e) {
		return;
	}
	QFAIL("No exception thrown when attributed an id to a report twice.");
}

/**
 * @brief Compares a serialized/deserialized report with the original report.
 */
void TestReport::testSerialize() {
	QJsonObject json;
	this->statistics.toJSON(json);
	Report test = StatisticsReport(json);

	QCOMPARE(test, this->statistics);
	QCOMPARE(test.getId(), this->statistics.getId());
	QCOMPARE(test.getDOCXFile(), this->statistics.getDOCXFile());
	QCOMPARE(test.getPDFFile(), this->statistics.getPDFFile());
	QCOMPARE(test.getType(), this->statistics.getType());
}
