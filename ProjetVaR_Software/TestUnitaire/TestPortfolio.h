#pragma once
#include <QTest>
#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QTest>
#include <QVector>
#include "Asset.h"
#include "Portfolio.h"

class TestPortfolio: public QObject {
    Q_OBJECT

public:
    TestPortfolio();

private Q_SLOTS:
    void testGetAsQVectors();

};
