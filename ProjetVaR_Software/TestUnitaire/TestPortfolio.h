#pragma once
#include <QTest>

class TestPortfolio: public QObject {
    Q_OBJECT

public:
    TestPortfolio();

private Q_SLOTS:
    void testGetAsQVectors();

};
