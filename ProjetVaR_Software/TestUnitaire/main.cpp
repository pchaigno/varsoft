#include "TestAsset.h"
#include "TestPortfolio.h"

int main() {
    int result = 0;

    TestAsset testAsset;
    result += QTest::qExec(&testAsset);

    TestPortfolio testPortfolio;
    result += QTest::qExec(&testPortfolio);

    return result;
}
