#include "TestAsset.h"

TestAsset::TestAsset() {}

void TestAsset::testGetValues() {

    qDebug() << "Current dir: " << QDir::currentPath();

    QDateTime startDate(QDate(2014, 1, 2), QTime(0, 0, 0));
    QDateTime endDate(QDate(2014, 1, 5), QTime(0, 0, 0));

    QString assetFolder = "../../CSV_examples/";

    Asset test1("test", assetFolder+"asset1.txt", startDate, endDate);
    Asset test2("test", assetFolder+"nonexistingfile.txt", startDate, endDate);

    QVector<double> result;

    try {
        result = test1.getValues(startDate, endDate);
    } catch(CannotOpenFileException& e) {
        qDebug() << e.what();
    }

    QCOMPARE(result.size(), 4);
    QCOMPARE(result.at(0), 101.0);
    QCOMPARE(result.at(1), 102.0);
    QCOMPARE(result.at(2), 103.0);
    QCOMPARE(result.at(3), 104.0);

    // NONEXISTING FILE CASE FOR ILLUSTRATION PURPOSES
    try {
        result = test2.getValues(startDate, endDate);
    } catch(CannotOpenFileException& e) {
        qDebug() << e.what();
    }
}
