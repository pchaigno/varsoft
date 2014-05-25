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
#include "TestPortfolio.h"

/**
 * @brief Initializes a few portfolio for the tests.
 */
TestPortfolio::TestPortfolio() {
	QString assetFolder = "../../Examples/";

	// FIRST ASSET DEFINITION
	QDate startDate1 = QDate(2014, 1, 1);
	QDate endDate1 = QDate(2014, 1, 6);
	Asset* asset1 = new Asset("asset1", assetFolder+"asset1.txt", "YAHOO", startDate1, endDate1);

	// SECOND ASSET DEFINITION
	QDate startDate2 = QDate(2014, 1, 2);
	QDate endDate2 = QDate(2014, 1, 7);
	Asset* asset2 = new Asset("asset2", assetFolder+"asset2.txt", "YAHOO", startDate2, endDate2);

	// THIRD ASSET DEFINITION
	QDate startDate3 = QDate(2014, 1, 3);
	QDate endDate3 = QDate(2014, 1, 8);
	Asset* asset3 = new Asset("asset3", assetFolder+"asset3.txt", "YAHOO", startDate3, endDate3);

	// FOURTH ASSET DEFINITION
	QDate startDate4 = QDate(2013, 12, 19);
	QDate endDate4 = QDate(2014, 1, 2);
	Asset* asset4 = new Asset("asset4", assetFolder+"asset4.txt", "YAHOO", startDate4, endDate4);

	// FIFTH ASSET DEFINITION
	QDate startDate5 = QDate(2013, 12, 19);
	QDate endDate5 = QDate(2014, 1, 3);
	Asset* asset5 = new Asset("asset5", assetFolder+"asset5.txt", "YAHOO", startDate5, endDate5);

	// SIXTH ASSET DEFINITION
	QDate startDate6 = QDate(2014, 01, 5);
	QDate endDate6 = QDate(2014, 01, 26);
	Asset* asset6 = new Asset("asset6", assetFolder+"asset6.txt", "ProjectVaR", startDate6, endDate6);

	// SEVENTH ASSET DEFINITION
	QDate startDate7 = QDate(2014, 01, 2);
	QDate endDate7 = QDate(2014, 03, 11);
	Asset* asset7 = new Asset("asset7", assetFolder+"dax.csv", "YAHOO", startDate7, endDate7);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(asset1, 1);
	assets.insert(asset2, 2);
	assets.insert(asset3, 3);

	QList<Report*> reports;
	this->father = Portfolio("Father", assets, reports);
	this->son = Portfolio(&father, "Son", assets, reports);

	// SECOND PORTFOLIO DEFINITION
	QMap<Asset*, int> assets2;
	assets2.insert(asset4, 1);
	assets2.insert(asset5, 2);
	QList<Report*> reports2;
	this->uncle = Portfolio("uncle", assets2, reports2);

	// THIRD PORTFOLIO DEFINITION
	QMap<Asset*, int> assets3;
	assets3.insert(asset6, 10);
	QList<Report*> reports3;
	this->weekends = Portfolio("weekends", assets3, reports3);

	// FOURTH PORTFOLIO DEFINITION
	QMap<Asset*, int> assets4;
	assets4.insert(asset7, 1);
	QList<Report*> reports4;
	this->auntie = Portfolio("dax", assets4, reports4);

	// CORRELATION TEST PORTFOLIO
	Asset* dax = new Asset("DAX", assetFolder+"dax.csv", "YAHOO", QDate(2014, 01, 2), QDate(2014, 03, 11));
	Asset* sp500 = new Asset("SP500", assetFolder+"sp500.csv", "YAHOO", QDate(2000, 01, 4), QDate(2014, 05, 22));
	Asset* gold = new Asset("Gold", assetFolder+"gold.csv", "YAHOO", QDate(2004, 11, 19), QDate(2014, 05, 22));
	QMap<Asset*, int> assets5;
	assets5.insert(dax, 1);
	assets5.insert(sp500, 1);
	assets5.insert(gold, 1);
	QList<Report*> reports5;
	this->correlation = Portfolio("correlations", assets5, reports5);
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestPortfolio::testId() {
	QCOMPARE(this->father.getId(), -1);
	QCOMPARE(this->son.getParentId(), -1);
	this->father.setId(42);
	QCOMPARE(this->father.getId(), 42);
	QVERIFY(this->father.isUpToDate());
	QCOMPARE(this->son.getParentId(), 42);
	try {
		this->father.setId(43);
		QFAIL("No exception thrown when attributed an id to a porfolio twice.");
	} catch(const IdAlreadyAttributedException e) {

	}
}

/**
 * @brief Checks that the name can actually be changed.
 */
void TestPortfolio::testName() {
	QVERIFY(this->father.getName() == "Father");
	this->father.changeName("John");
	QVERIFY(this->father.getName() == "John");
	QVERIFY(this->father.isModified());
}

/**
 * @brief Tests the retrieveStartDate method.
 */
void TestPortfolio::testRetrieveStartDate() {
	QCOMPARE(this->father.retrieveStartDate(), QDate(2014, 1, 3));
	QCOMPARE(this->son.retrieveStartDate(), QDate(2014, 1, 3));
	QCOMPARE(this->uncle.retrieveStartDate(), QDate(2013, 12, 19));
}

/**
 * @brief Tests the retrieveStartDate method.
 */
void TestPortfolio::testRetrieveEndDate() {
	QCOMPARE(this->father.retrieveEndDate(), QDate(2014, 1, 6));
	QCOMPARE(this->son.retrieveEndDate(), QDate(2014, 1, 6));
	QCOMPARE(this->uncle.retrieveEndDate(), QDate(2014, 1, 2));
}

/**
 * @brief Tests the method getValues that retrieve and compute values of a portfolio.
 */
void TestPortfolio::testRetrieveValues() {
	QVector<double> result = this->son.retrieveValues(QDate(2014, 1, 4), QDate(2014, 1, 6));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 630.0);
}

/**
 * @brief Tests the method getValues that retrieve and compute values of a portfolio.
 * The only asset of this portfolio is only defined on weekends.
 */
void TestPortfolio::testRetrieveValuesWeekends() {
	QVector<double> result = this->weekends.retrieveValues();
	QCOMPARE(result.size(), 15);
	QMap<QDate, double> resultWithDates = this->weekends.retrieveValuesByDate();
	QCOMPARE(resultWithDates.size(), 15);
}

/**
 * @brief Successful test of retrieveValues without parameters.
 */
void TestPortfolio::testRetrieveValuesNoParameters() {
	QVector<double> result = this->son.retrieveValues();
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.at(0), 612.0);
	QCOMPARE(result.at(1), 630.0);
}

/**
 * @brief Tests the method retrieveValuesByDate that retrieve and compute date-values of a portfolio
 */
void TestPortfolio::testRetrieveValuesByDate() {
	QMap<QDate, double> result = this->son.retrieveValuesByDate(QDate(2014, 1, 4), QDate(2014, 1, 6));
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.value(QDate(2014, 1, 6)), 630.0);
}

/**
 * @brief Tests of retrieveValuesByDate when the period is larger than the portfolio's period.
 */
void TestPortfolio::testRetrieveValuesByDateMissingValues() {
	QMap<QDate, double> result = this->son.retrieveValuesByDate(QDate(2014, 1, 2), QDate(2014, 1, 8));
	QCOMPARE(result.size(), 2);
	QCOMPARE(result.value(QDate(2014, 1, 3)), 612.0);
	QCOMPARE(result.value(QDate(2014, 1, 6)), 630.0);
}

/**
 * @brief Tests the retrieveReturns method without parameters.
 * This method calls directly the eponymous method on the whole definition period of the portfolio.
 */
void TestPortfolio::testRetrieveReturns() {
	QVector<double> result = this->son.retrieveReturns();
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 18.0);
}

/**
 * @brief Tests the the retrieveReturns methods with a small number of values to return.
 * The portfolio son only contains 2 values (so only 1 returns).
 */
void TestPortfolio::testRetrieveNbReturnsNotEnough() {
	QVector<double> result = this->son.retrieveReturns(this->son.retrieveEndDate(), 2);
	QCOMPARE(result.size(), 1);
	QCOMPARE(result.at(0), 18.0);
}

/**
 * @brief Tests the the retrieveReturns methods with a small number of values to return.
 * The portfolio uncle contains 11 values (so 10 returns).
 * This test retrieves all returns.
 */
void TestPortfolio::testRetrieveNbReturnsAll() {
	QVector<double> result = this->uncle.retrieveReturns(this->uncle.retrieveEndDate(), 10);
	QCOMPARE(result.size(), 10);
	QCOMPARE(result.at(0), 20.0);
	QCOMPARE(result.at(1), 2.0);
	QCOMPARE(result.at(2), 2.0);
	QCOMPARE(result.at(3), 2.0);
	QCOMPARE(result.at(4), 5.0);
	QCOMPARE(result.at(5), -20.0);
	QCOMPARE(result.at(6), 11.0);
	QCOMPARE(result.at(7), 0.0);
	QCOMPARE(result.at(8), 4.0);
	QCOMPARE(result.at(9), 1.0);
}

/**
 * @brief Tests the the retrieveReturns methods with a small number of values to return.
 * The portfolio uncle contains 11 values (so 10 returns).
 * This test only retrieves 4 returns.
 */
void TestPortfolio::testRetrieveNbReturnsSome() {
	QVector<double> result = this->uncle.retrieveReturns(this->uncle.retrieveEndDate(), 4);
	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 11.0);
	QCOMPARE(result.at(1), 0.0);
	QCOMPARE(result.at(2), 4.0);
	QCOMPARE(result.at(3), 1.0);
}

/**
 * @brief Tests the testRetrieveReturnHorizon in normal cases
 */
void TestPortfolio::testRetrieveReturnHorizon() {
	QCOMPARE(this->auntie.retrieveReturnHorizon(QDate(2014, 3, 11), 1), 42.29);
	QCOMPARE(this->auntie.retrieveReturnHorizon(QDate(2014, 3, 10), 1), -85.25);
	QCOMPARE(this->auntie.retrieveReturnHorizon(QDate(2014, 3, 7), 2), -277.37);
	QCOMPARE(this->auntie.retrieveReturnHorizon(QDate(2014, 2, 28), 2), -229.44);
	QCOMPARE(this->auntie.retrieveReturnHorizon(QDate(2014, 1, 3), 1), 35.11);
	QCOMPARE(this->auntie.retrieveReturnHorizon(QDate(2014, 2, 11), 5), 366.9);
}

/**
 * @brief Tests the testRetrieveReturnHorizon behaviour with wrong parameters combinaisons
 */
void TestPortfolio::testRetrieveReturnHorizonIncorrect() {
	try {
		this->auntie.retrieveReturnHorizon(QDate(2014, 1, 2), 1);
		QFAIL("retrieveReturnHorizon was able to retrieve a return with wrong parameter");
	} catch(std::exception& e) {}

	try {
		this->auntie.retrieveReturnHorizon(QDate(2014, 3, 11), 2);
		QFAIL("retrieveReturnHorizon was able to retrieve a return with wrong parameters combinaison");
	} catch(std::exception& e) {}

	try {
		this->auntie.retrieveReturnHorizon(QDate(2014, 3, 7), 4);
		QFAIL("retrieveReturnHorizon was able to retrieve a return with wrong parameters combinaison");
	} catch(std::exception& e) {}
}

/**
 * @brief Tests the computation of the correlation matrix of a portfolio
 */
void TestPortfolio::testComputeCorrelationMatrix() {
	QDate startDate(2014, 1, 3);
	QDate endDate(2014, 3, 1);
	QVector<QVector<double> > correlationMatrix = this->correlation.computeCorrelationMatrix(startDate, endDate);
	QVector<double> values0 = this->correlation.getAssets().at(0)->retrieveValues(startDate, endDate);
	QVector<double> values1 = this->correlation.getAssets().at(1)->retrieveValues(startDate, endDate);
	QVector<double> values2 = this->correlation.getAssets().at(2)->retrieveValues(startDate, endDate);
	QCOMPARE(correlationMatrix[0][0], 1.0);
	QCOMPARE(correlationMatrix[0][1], MathFunctions::correlation(values0, values1));
	QCOMPARE(correlationMatrix[0][2], MathFunctions::correlation(values0, values2));
	QCOMPARE(correlationMatrix[1][0], MathFunctions::correlation(values1, values0));
	QCOMPARE(correlationMatrix[1][1], 1.0);
	QCOMPARE(correlationMatrix[1][2], MathFunctions::correlation(values1, values2));
	QCOMPARE(correlationMatrix[2][0], MathFunctions::correlation(values2, values0));
	QCOMPARE(correlationMatrix[2][1], MathFunctions::correlation(values2, values1));
	QCOMPARE(correlationMatrix[2][2], 1.0);
}

/**
 * @brief Tests that incorrect date parameter prevents the function from
 * computing the correlation matrix
 */
void TestPortfolio::testComputeCorrelationMatrixIncorrect() {
	try {
		this->correlation.computeCorrelationMatrix(QDate(2014, 1, 3), QDate(2014, 3, 12));
		QFAIL("computeCorrelatioMatrix computed the matrix correlation despite a wrong parameter");
	} catch(std::invalid_argument& e) {

	}
}

/**
 * @brief Compares two serialized/deserialized portfolios with the originals.
 * The first one is the parent of the second one.
 */
void TestPortfolio::testSerialize() {
	// The portfolios father and son have IDs.
	QJsonObject jsonParent = this->father.toJSON();
	QJsonObject jsonSon = this->son.toJSON();
	// We need to save the assets in the database to be able to deserialize them:
	// The two portfolios share the same assets.
	foreach(Asset* asset, this->father.getAssets()) {
		SessionSaver::getInstance()->saveAsset(*asset);
	}

	Portfolio serializedFather;
	Portfolio serializedSon;
	QMap<QString, Portfolio*> portfoliosDeserialized;
	try {
		serializedFather = Portfolio(jsonParent, portfoliosDeserialized);
		serializedSon = Portfolio(jsonSon, portfoliosDeserialized);
	} catch(NonexistentAssetException e) {
		QFAIL(e.what());
	}

	comparePortfolios(serializedFather, this->father);
	comparePortfolios(serializedSon, this->son);

	// Deletes the database created at the beginning of the test:
	QFile databaseFile(SessionSaver::getInstance()->getDatabaseFile());
	databaseFile.remove();
}

/**
 * @brief Compares a serialized/deserialized portfolio with its original.
 * The assets, the reports and the attributes are compared.
 * @param serializedPortfolio The serialized/deserialized portfolio.
 * @param portfolio The original portfolio.
 */
void TestPortfolio::comparePortfolios(Portfolio& serializedPortfolio, Portfolio& portfolio) {
	QCOMPARE(serializedPortfolio.getId(), -1);
	QCOMPARE(serializedPortfolio.getName(), portfolio.getName());
	if(portfolio.getParent() != NULL) {
		QCOMPARE(*serializedPortfolio.getParent(), *portfolio.getParent());
	}
	QCOMPARE(serializedPortfolio.getParentId(), -1);
	// Compares the reports:
	QCOMPARE(serializedPortfolio.getReports().size(), portfolio.getReports().size());
	foreach(const Report* serializedReport, serializedPortfolio.getReports()) {
		bool reportFound = false;
		foreach(const Report* report, portfolio.getReports()) {
			if(report->getFile() == serializedReport->getFile()) {
				QCOMPARE(serializedReport->getType(), report->getType());
				reportFound = true;
				break;
			}
		}
		QVERIFY(reportFound);
	}
	// Compares the assets and the weights:
	QCOMPARE(serializedPortfolio.getAssets().size(), portfolio.getAssets().size());
	foreach(Asset* const serializedAsset, serializedPortfolio.getAssets()) {
		bool assetFound = false;
		foreach(Asset* const asset, portfolio.getAssets()) {
			if(asset->getName() == serializedAsset->getName()) {
				QCOMPARE(serializedPortfolio.getWeight(serializedAsset), portfolio.getWeight(asset));
				assetFound = true;
				break;
			}
		}
		QVERIFY(assetFound);
	}
}
