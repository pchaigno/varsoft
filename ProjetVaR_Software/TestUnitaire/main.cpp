#include "TestAsset.h"
#include "TestPortfolio.h"
#include "TestVaRHistorical.h"

int main() {
    int result = 0;

    TestAsset testAsset;
    result += QTest::qExec(&testAsset);

    TestPortfolio testPortfolio;
    result += QTest::qExec(&testPortfolio);

    TestVaRHistorical testVaRHistorical;
    result += QTest::qExec(&testVaRHistorical);

    return result;
}
