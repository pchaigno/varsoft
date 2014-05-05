#pragma once

#include <QtTest>
#include "ExportManager.h"
#include "ImportManager.h"
#include "TestPortfolio.h"
#include <QString>

class TestArchiveManagers: public QObject {
	Q_OBJECT

private:
	QVector<Portfolio*> portfolios;
	Asset google;
	Asset apple;

public:
	TestArchiveManagers();

private Q_SLOTS:
	void testExportPortfolios();
};
