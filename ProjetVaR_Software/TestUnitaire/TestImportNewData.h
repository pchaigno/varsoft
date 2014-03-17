#pragma once
#include "ImportNewData.h"
#include <QtTest>
class TestImportNewData: public QObject {
    Q_OBJECT

private:
    QString stockName;
    QString firstDate;
    QString lastDate;
    QString origin;
    QString newFile;

public:
    TestImportNewData();

private Q_SLOTS:
    void testDates();
};
