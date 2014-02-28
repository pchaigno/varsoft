#include "TestAsset.h"
#include "TestPortfolio.h"
#include "TestReport.h"
#include "TestSQLiteManagers.h"

int main() {
	TestAsset asset;
	QTest::qExec(&asset);
	TestPortfolio portfolio;
	QTest::qExec(&portfolio);
	TestReport report;
	QTest::qExec(&report);
	TestSQLiteManagers sqlite;
	QTest::qExec(&sqlite);
	return 0;
}