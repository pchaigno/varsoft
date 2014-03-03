#pragma once
#include <QTest>

class TestAsset: public QObject {
    Q_OBJECT

public:
    TestAsset();

private Q_SLOTS:
    void testGetAsQVectors();

};
