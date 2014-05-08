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
	QVector<Report*> reports;
	reports.append(new GarchReport("somefolder\\garch.docx", "somefolder\\garch.pdf"));
	reports.append(new VaRReport("somefolder\\var.docx", "somefolder\\var.pdf"));

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
