
#include "TestImportData.h"
#include "TestImportNewData.h"

int main() {
    int result = 0;
    TestImportNewData newdata;
    result += QTest::qExec(&newdata);
    TestImportData data;
    result += QTest::qExec(&data);
    return result;
}
