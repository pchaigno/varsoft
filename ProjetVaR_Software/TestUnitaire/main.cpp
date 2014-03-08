#include "TestImportData.h"
#include "TestImportNewData.h"
#include "TestAsset.h"
#include "TestPortfolio.h"

int main() {
    int result = 0;
	TestAsset testAsset;
	result += QTest::qExec(&testAsset);
	TestPortfolio testPortfolio;
	result += QTest::qExec(&testPortfolio);
    TestImportNewData newdata;
    result += QTest::qExec(&newdata);
    TestImportData data;
	result += QTest::qExec(&data);
	return result;
}
