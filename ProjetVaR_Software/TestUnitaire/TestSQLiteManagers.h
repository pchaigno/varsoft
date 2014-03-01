#pragma once

#include <QtTest>
#include "Portfolio.h"
#include "Asset.h"
#include "GarchReport.h"
#include "VaRReport.h"
#include "SessionSaver.h"
#include "SessionBuilder.h"

class TestSQLiteManagers: public QObject {
	Q_OBJECT

private:
	QVector<Portfolio> portfolios;
    Asset google;
    Asset apple;

public:
	TestSQLiteManagers();

private Q_SLOTS:
	void testSaveSession();
};