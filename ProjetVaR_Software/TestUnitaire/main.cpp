#include "TestAsset.h"
#include "TestPortfolio.h"
#include "TestReport.h"
#include <QtWidgets/QApplication>

int main() {
	TestAsset asset;
	QTest::qExec(&asset);
	TestPortfolio portfolio;
	QTest::qExec(&portfolio);
	TestReport report;
	QTest::qExec(&report);
	return 0;
}