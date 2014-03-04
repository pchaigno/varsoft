#pragma once
#include <QDir>
#include <QTest>
#include <QVector>
#include "Asset.h"

class TestAsset: public QObject {
    Q_OBJECT

public:
    TestAsset();

private Q_SLOTS:
    void testGetAsQVectors();

};
