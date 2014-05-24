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
#include "TestSQLiteManagers.h"

/**
 * @brief Initializes a portfolio and a few assets.
 */
TestSQLiteManagers::TestSQLiteManagers() {
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
	this->garchReport = new GarchReport("somefolder\\garch");
	reports.append(this->garchReport);
	this->varReport = new VaRReport("somefolder\\var");
	reports.append(this->varReport);

	// The portfolio:
	Portfolio* portfolio = new Portfolio("Test", assets, reports);
	this->portfolios = QList<Portfolio*>();
	portfolio = new Portfolio("ToBeRemoved", assets, reports);
	this->portfolios.append(portfolio);
}

void TestSQLiteManagers::testSaveSession() {
	// Save everything in the database:
	SessionSaver::getInstance()->saveSession(this->portfolios);

	// Checks that all ids have been updated:
	foreach(Portfolio* portfolio, this->portfolios) {
		QVERIFY(portfolio->getId() > 0);
		QVERIFY(portfolio->isUpToDate());
		const QList<Report*>& reports = portfolio->getReports();
		for(int j=0; j<reports.size(); j++) {
			QVERIFY(reports[j]->getId() > 0);
			QVERIFY(reports[j]->isUpToDate());
		}
	}
	QVERIFY(this->apple.getId() > 0);
	QVERIFY(this->apple.isUpToDate());
	QVERIFY(this->google.getId() > 0);
	QVERIFY(this->google.isUpToDate());

	// Retrieves everything from the database:
	QMap<QString, Asset*> assets = SessionBuilder::getInstance()->buildAssets();

	// Checks that the assets are here:
	QVERIFY(*(assets["Apple"]) == this->apple);
	QVERIFY(*(assets["Google"]) == this->google);
	QVERIFY(assets["Apple"]->isUpToDate());
	QVERIFY(assets["Google"]->isUpToDate());
	QVERIFY(assets["Apple"]->getOrigin() == this->apple.getOrigin());
	QVERIFY(assets["Google"]->getOrigin() == this->google.getOrigin());
	QVERIFY(assets["Apple"]->getFile() == this->apple.getFile());
	QVERIFY(assets["Google"]->getFile() == this->google.getFile());
	QCOMPARE(assets["Apple"]->getStartDate(), this->apple.getStartDate());
	QCOMPARE(assets["Google"]->getStartDate(), this->google.getStartDate());
	QCOMPARE(assets["Apple"]->getEndDate(), this->apple.getEndDate());
	QCOMPARE(assets["Google"]->getEndDate(), this->google.getEndDate());

	// Checks the portfolios:
	QList<Portfolio*> savedPortfolios = SessionBuilder::getInstance()->buildSession();
	QCOMPARE(savedPortfolios.size(), this->portfolios.size());
	foreach(Portfolio* portfolio, this->portfolios) {
		int idPortfolio = -1;
		for(int j=0; idPortfolio==-1 && j<savedPortfolios.size(); j++) {
			if(*savedPortfolios[j] == *portfolio) {
				idPortfolio = j;
			}
		}
		QVERIFY(idPortfolio != -1);

		// Checks the reports:
		const QList<Report*>& savedReports = savedPortfolios[idPortfolio]->getReports();
		const QList<Report*>& reports = portfolio->getReports();
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
		const QMap<Asset*, int>& savedComposition = savedPortfolios[idPortfolio]->getComposition();
		const QMap<Asset*, int>& composition = portfolio->getComposition();
		for(QMap<Asset*, int>::const_iterator it=composition.begin(); it!=composition.end(); ++it) {
			bool found = false;
			for(QMap<Asset*, int>::const_iterator savedIt=savedComposition.begin(); savedIt!=savedComposition.end(); ++savedIt) {
				if(*(it.key()) == *(savedIt.key())) {
					QCOMPARE(savedIt.value(), it.value());
					found = true;
				}
			}
			QVERIFY(found);
		}
	}
}

/**
 * @brief Tests the save mechanism when the session has been updated (name changed, reports deleted/added).
 */
void TestSQLiteManagers::testUpdateSession() {
	// Modify the session:
	this->apple.changeName("Pomme");
	this->portfolios[0]->changeName("Updated");
	this->portfolios[0]->removeReport(this->varReport);
	Report* statisticsReport = new StatisticsReport("somefolder/statisticsReport");
	this->portfolios[0]->addReport(statisticsReport);
	this->portfolios.removeAt(1);
	SessionSaver::getInstance()->saveSession(this->portfolios);

	// Retrieves everything from the database:
	QMap<QString, Asset*> assets = SessionBuilder::getInstance()->buildAssets();

	// Checks that the assets are here:
	QVERIFY(*(assets["Pomme"]) == this->apple);
	QVERIFY(*(assets["Google"]) == this->google);
	QVERIFY(assets["Pomme"]->isUpToDate());
	QVERIFY(assets["Google"]->isUpToDate());
	QVERIFY(assets["Pomme"]->getOrigin() == this->apple.getOrigin());
	QVERIFY(assets["Google"]->getOrigin() == this->google.getOrigin());
	QVERIFY(assets["Pomme"]->getFile() == this->apple.getFile());
	QVERIFY(assets["Google"]->getFile() == this->google.getFile());
	QCOMPARE(assets["Pomme"]->getStartDate(), this->apple.getStartDate());
	QCOMPARE(assets["Google"]->getStartDate(), this->google.getStartDate());
	QCOMPARE(assets["Pomme"]->getEndDate(), this->apple.getEndDate());
	QCOMPARE(assets["Google"]->getEndDate(), this->google.getEndDate());

	// Checks the portfolios:
	QList<Portfolio*> savedPortfolios = SessionBuilder::getInstance()->buildSession();
	QCOMPARE(savedPortfolios.size(), this->portfolios.size());
	foreach(Portfolio* portfolio, this->portfolios) {
		int idPortfolio = -1;
		for(int j=0; idPortfolio==-1 && j<savedPortfolios.size(); j++) {
			if(*savedPortfolios[j] == *portfolio) {
				idPortfolio = j;
			}
		}
		QVERIFY(idPortfolio != -1);

		// Checks the reports:
		const QList<Report*>& savedReports = savedPortfolios[idPortfolio]->getReports();
		const QList<Report*>& reports = portfolio->getReports();
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
		const QMap<Asset*, int>& savedComposition = savedPortfolios[idPortfolio]->getComposition();
		const QMap<Asset*, int>& composition = portfolio->getComposition();
		for(QMap<Asset*, int>::const_iterator it=composition.begin(); it!=composition.end(); ++it) {
			bool found = false;
			for(QMap<Asset*, int>::const_iterator savedIt=savedComposition.begin(); savedIt!=savedComposition.end(); ++savedIt) {
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
