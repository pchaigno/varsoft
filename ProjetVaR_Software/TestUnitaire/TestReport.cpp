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