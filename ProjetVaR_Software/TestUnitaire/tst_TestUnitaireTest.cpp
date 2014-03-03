#include <QString>
#include <QtTest>

class TestUnitaireTest : public QObject
{
    Q_OBJECT

public:
    TestUnitaireTest();

private Q_SLOTS:
    void testCase1();
};

TestUnitaireTest::TestUnitaireTest()
{
}

void TestUnitaireTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

//QTEST_APPLESS_MAIN(TestUnitaireTest)

#include "tst_TestUnitaireTest.moc"
