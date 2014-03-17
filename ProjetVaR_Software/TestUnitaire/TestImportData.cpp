#include "TestImportData.h"

/**
* @brief Initializes an asset for the tests.
*/
TestImportData::TestImportData() {
    TestImportData::stockName = "Gogole";
    TestImportData::firstDate = "2014-01-02";
    TestImportData::lastDate = "2014-01-01";
    TestImportData::origin = "Yahoo";
}

/**
* @brief Checks that the firstDate and the lastDate of the generated file correspond to the params
*/
void TestImportData::testDates() {
}


/**
* @brief Checks that the name can actually be changed.
*/
void TestImportData::testName() {
}
