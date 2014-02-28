#include "TestSQLiteManagers.h"

TestSQLiteManagers::TestSQLiteManagers() {
	QDateTime firstDate;
	QDateTime lastDate;
	this->apple = new Asset("Apple", "somefolder\\apple.csv", "YAHOO", firstDate, lastDate);
	this->google = new Asset("Google", "somefolder\\google.csv", "YAHOO", firstDate, lastDate);
	QMap<Asset*, int> assets = QMap<Asset*, int>();
	assets[this->google] = 5;
	assets[this->google] = 4;

	this->garchReport = GarchReport("somefolder\\garch.docx", "somefolder\\garch.pdf");
	this->varReport = GarchReport("somefolder\\var.docx", "somefolder\\var.pdf");
	QVector<Report> reports = QVector<Report>();
	reports.append(this->garchReport);
	reports.append(this->varReport);

	Portfolio portfolio = Portfolio("Test", assets, reports);
	this->portfolios = QVector<Portfolio>();
	this->portfolios.append(portfolio);
}

void TestSQLiteManagers::testSaveSession() {
	SessionSaver::getInstance()->saveSession(this->portfolios);
	for(int i=0; i<this->portfolios.size(); i++) {
		QVERIFY(this->portfolios.at(i).getId() != -1);
	}
	QVERIFY(this->apple->getId() != -1);
	QVERIFY(this->google->getId() != -1);
	QVERIFY(this->garchReport.getId() != -1);
	QVERIFY(this->varReport.getId() != -1);

	QVector<Asset> assets = SessionBuilder::getInstance()->buildAssets();
	QVERIFY(assets.contains(*this->apple));
	QVERIFY(assets.contains(*this->google));

	QVector<Portfolio> savedPortfolios = SessionBuilder::getInstance()->buildSession();
	for(int i=0; i<this->portfolios.size(); i++) {
		QVERIFY(savedPortfolios.contains(this->portfolios.at(i)));
	}
}