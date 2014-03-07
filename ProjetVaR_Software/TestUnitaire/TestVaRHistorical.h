#pragma once
#include <QDebug>
#include <QTest>
#include "Asset.h"
#include "Portfolio.h"
#include "Report.h"
#include "VaRHistorical.h"

class TestVaRHistorical: public QObject {
    Q_OBJECT

public:
    TestVaRHistorical();

private Q_SLOTS:
    void testExecute();
};

