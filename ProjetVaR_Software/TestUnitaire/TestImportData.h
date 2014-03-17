#pragma once
#include "ImportData.h"
#include <QtTest>
class TestImportData: public QObject {
    Q_OBJECT

private:
    QString stockName;
    QString firstDate;
    QString lastDate;
    QString origin;

public:
    TestImportData();

private Q_SLOTS:
    void testDates();
};
