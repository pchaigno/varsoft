#include "TestImportData.h"
#include "TestImportNewData.h"
#include "TestAsset.h"
#include "TestPortfolio.h"
#include "TestReport.h"
#include "TestSQLiteManagers.h"

int main() {
    int result = 0;
	TestAsset asset;
	result += QTest::qExec(&asset);
	TestPortfolio portfolio;
	result += QTest::qExec(&portfolio);
	TestReport report;
	result += QTest::qExec(&report);
	TestSQLiteManagers sqlite;
	result += QTest::qExec(&sqlite);
    TestImportNewData newdata;
    result += QTest::qExec(&newdata);
    TestImportData data;
	result += QTest::qExec(&data);
	return result;
}
