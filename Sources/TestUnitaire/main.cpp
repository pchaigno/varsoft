/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "TestCreateAsset.h"
#include "TestAsset.h"
#include "TestPortfolio.h"
#include "TestVaRHistorical.h"
#include "TestVaRRiskmetrics.h"
#include "TestReport.h"
#include "TestSQLiteManagers.h"
#include "TestArchiveManagers.h"
#include "TestMathFunctions.h"
#include "TestRInterface.h"
#include "TestVaRGarch.h"
#include "TestBacktesting.h"

int main() {
	// Deletes the database file before starting the tests (just to be sure):
	QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
	databaseFile.remove();

	int result = 0;
	TestAsset asset;
	result += QTest::qExec(&asset);
	TestPortfolio portfolio;
	result += QTest::qExec(&portfolio);
	TestReport report;
	result += QTest::qExec(&report);
	TestSQLiteManagers sqlite;
	result += QTest::qExec(&sqlite);
	TestVaRHistorical testVaRHistorical;
	result += QTest::qExec(&testVaRHistorical);
	TestVaRRiskmetrics TestVaRRiskmetrics;
	result += QTest::qExec(&TestVaRRiskmetrics);
	TestVaRGarch varGarch;
	result += QTest::qExec(&varGarch);
	TestMathFunctions testMathFunctions;
	result += QTest::qExec(&testMathFunctions);
	TestCreateAsset newdata;
	result += QTest::qExec(&newdata);
	/*
	TestPortfolioItemModel portfolioModel;
	result += QTest::qExec(&portfolioModel);*/
	TestArchiveManagers archiveManager;
	result += QTest::qExec(&archiveManager);
	TestRInterface rInterface;
	result += QTest::qExec(&rInterface);
	TestBacktesting backtesting;
	result += QTest::qExec(&backtesting);
	return result;
}
