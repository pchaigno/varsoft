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
#include "TestArchiveManagers.h"

TestArchiveManagers::TestArchiveManagers() {
	// The assets:
	QDate startDate = QDate::fromString("010198", "ddMMyy");
	QDate endDate = QDate::fromString("03122014", "ddMMyyyy");
	this->apple = Asset("Apple", "somefolder\\apple.csv", "YAHOO", startDate, endDate);
	this->google = Asset("Google", "somefolder\\google.csv", "YAHOO", startDate, endDate);
	QMap<Asset*, int> assets = QMap<Asset*, int>();
	assets[&(this->google)] = 5;
	assets[&(this->apple)] = 4;

	// The reports for the portfolio:
	QList<Report*> reports;
	reports.append(new GarchReport("somefolder/garch"));
	reports.append(new VaRReport("somefolder/var"));

	// The portfolio:
	Portfolio* portfolio = new Portfolio("Test", assets, reports);
	this->portfolios.append(portfolio);
}

/**
 * @brief Functional test: export then import a set of portfolios and compare them to the originals.
 */
void TestArchiveManagers::testExportImportPortfolios() {
	// The assets need to be in the database to be serialized:
	SessionSaver::getInstance()->saveAsset(this->apple);
	SessionSaver::getInstance()->saveAsset(this->google);

	ExportManager exportManager = ExportManager("test.zip");
	try {
		exportManager.exportArchive(this->portfolios);
	} catch(ExportException e) {
		QFAIL(e.what());
	}
	QFile archiveFile("test.zip");
	QVERIFY(archiveFile.exists());

	ImportManager importManager = ImportManager("test.zip");
	try {
		importManager.importArchive();
	} catch(ImportException e) {
		QFAIL(e.what());
	}
	QVector<Portfolio*> portfoliosImported = importManager.getPortfolios();

	QCOMPARE(portfoliosImported.size(), this->portfolios.size());
	foreach(Portfolio* portfolio, this->portfolios) {
		bool found = false;
		foreach(Portfolio* portfolioImported, portfoliosImported) {
			if(*portfolio == *portfolioImported) {
				found = true;
				TestPortfolio::comparePortfolios(*portfolioImported, *portfolio);
			}
		}
		QVERIFY(found);
	}

	archiveFile.remove();
	// Deletes the database created at the beginning of the test:
	QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
	databaseFile.remove();
}

/**
 * @brief Very simple test which tries to open a missing archive.
 */
void TestArchiveManagers::testMissingArchive() {
	ImportManager importManager = ImportManager("missing.zip");
	try {
		importManager.importArchive();
		QFAIL("ImportManager should have thrown an exception since the archive is missing.");
	} catch(ImportException e) {}
}

/**
 * @brief Very simple test which tries to open a missing archive.
 */
void TestArchiveManagers::testEmptyArchive() {
	ImportManager importManager = ImportManager("../../Examples/nodescriptor.zip");
	try {
		importManager.importArchive();
		QFAIL("ImportManager should have thrown an exception since the archive is empty.");
	} catch(ImportException e) {}
}
