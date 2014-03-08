#include "TestSQLiteManagers.h"

/**
 * @brief Initializes a portfolio and a few assets.
 */
TestSQLiteManagers::TestSQLiteManagers() {
	// The assets:
	QDateTime firstDate;
	QDateTime lastDate;
	this->apple = Asset("Apple", "somefolder\\apple.csv", "YAHOO", firstDate, lastDate);
	this->google = Asset("Google", "somefolder\\google.csv", "YAHOO", firstDate, lastDate);
	QMap<Asset*, int> assets = QMap<Asset*, int>();
	assets[&(this->google)] = 5;
	assets[&(this->apple)] = 4;

	// The reports for the portfolio:
	QVector<Report*> reports;
	reports.append(new GarchReport("somefolder\\garch.docx", "somefolder\\garch.pdf"));
	reports.append(new VaRReport("somefolder\\var.docx", "somefolder\\var.pdf"));

	// The portfolio:
	Portfolio portfolio = Portfolio("Test", assets, reports);
	this->portfolios = QVector<Portfolio>();
	this->portfolios.append(portfolio);
}

void TestSQLiteManagers::testSaveSession() {
	// Save everything in the database:
	SessionSaver::getInstance()->saveSession(this->portfolios);

	// Checks that all ids have been updated:
	for(int i=0; i<this->portfolios.size(); i++) {
		QVERIFY(this->portfolios[i].getId() > 0);
		const QVector<Report*>& reports = this->portfolios[i].getReports();
		for(int j=0; j<reports.size(); j++) {
			QVERIFY(reports[j]->getId() > 0);
		}
	}
	QVERIFY(this->apple.getId() > 0);
	QVERIFY(this->google.getId() > 0);

	// Retrieves everything from the database:
	QMap<QString, Asset*> assets = SessionBuilder::getInstance()->buildAssets();

	// Checks that the assets are here:
	QVERIFY(*(assets["Apple"]) == this->apple);
	QVERIFY(*(assets["Google"]) == this->google);

	// Checks the portfolios:
	QVector<Portfolio> savedPortfolios = SessionBuilder::getInstance()->buildSession();
	QCOMPARE(savedPortfolios.size(), this->portfolios.size());
	for(int i=0; i<this->portfolios.size(); i++) {
		QVERIFY(savedPortfolios.contains(this->portfolios[i]));
		int idPortfolio = -1;
		for(int j=0; idPortfolio==-1 && j<savedPortfolios.size(); j++) {
			if(savedPortfolios[j] == this->portfolios[i]) {
				idPortfolio = j;
			}
		}
		QVERIFY(idPortfolio != -1);

		// Checks the reports:
		const QVector<Report*>& savedReports = savedPortfolios[idPortfolio].getReports();
		const QVector<Report*>& reports = this->portfolios[i].getReports();
		QCOMPARE(savedReports.size(), reports.size());
		for(int j=0; j<savedReports.size(); j++) {
			bool found = false;
			for(int k=0; k<reports.size(); k++) {
				if(*(reports[k]) == *(savedReports[j])) {
					found = true;
				}
			}
			QVERIFY(found);
			QVERIFY(savedReports[j]->getType() != NONE);
		}

		// Checks the compositions:
		const QMap<Asset*, int>& savedComposition = savedPortfolios[idPortfolio].getComposition();
		const QMap<Asset*, int>& composition = this->portfolios[i].getComposition();
		for(QMap<Asset*, int>::const_iterator it=composition.begin(); it!=composition.end(); ++it) {
			bool found = false;
			for(QMap<Asset*, int>::const_iterator savedIt=composition.begin(); savedIt!=composition.end(); ++savedIt) {
				if(*(it.key()) == *(savedIt.key())) {
					QCOMPARE(savedIt.value(), it.value());
					found = true;
				}
			}
			QVERIFY(found);
		}
	}

	// Deletes the database file:
	QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
	databaseFile.remove();
}
