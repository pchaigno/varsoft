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
#include "TestVaRHistorical.h"

/**
 * @brief Creates the portfolio to perform Value-at-Risk computation on it
 */
TestVaRHistorical::TestVaRHistorical() {
	QString assetFolder = "../../Examples/";

	// ASSET DEFINITION
	QDate startDate(QDate(2014, 1, 2));
	QDate endDate(QDate(2014, 3, 11));
	Asset* dax = new Asset("dax", assetFolder+"dax.csv", "YAHOO", startDate, endDate);

	// TEST PORTFOLIO DEFINITION
	QMap<Asset*, int> assets;
	assets.insert(dax, 1);
	QList<Report*> reports;
	this->daxPortfolio = Portfolio("daxPortfolio", assets, reports);
}

/**
 * @brief Tests the VaRHistorical consctructor and also indirectly the VaRAlgorithm one
 */
void TestVaRHistorical::testVaRHistoricalConstructor() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 0; // INTENDED INCORRECT VALUE

	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong returnsPeriod parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	// ANOTHER IMPOSSIBLE CASE
	returnsPeriod = -3;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong returnsPeriod parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	// INCORRECT RISK
	returnsPeriod = 10;
	risk = 0;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong risk parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	risk = 1;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong risk parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	risk = 1.5;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong risk parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	// INCORRECT TIME HORIZON
	risk = 0.05;
	timeHorizon = 0;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong timeHorizon parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}

	timeHorizon = -1;
	try {
		VaRHistorical daxVaR(daxPortfolio, risk, timeHorizon, returnsPeriod);
		QFAIL("VaRHistorical constructor succeeded despite wrong timeHorizon parameter");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests a normal Value-at-Risk computation
 */
void TestVaRHistorical::testExecute() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 45;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		double var = daxVaR.execute(QDate(2014, 3, 12));
		// Compares the computed VaR matches with the manually found one
		QCOMPARE(var, 239.02);
	} catch(std::exception& e) {
		qDebug() << e.what();
		QFAIL("Value-at-Risk should have been successfuly computed.");
	}
}

/**
 * @brief Tests a normal Value-at-Risk computation with a 3 days time horizon
 */
void TestVaRHistorical::testExecuteThreeDaysTimeHorizon() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 3;
	int returnsPeriod = 45;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		double var = daxVaR.execute(QDate(2014, 3, 12));
		// Compares the computed VaR matches with the manually found one
		QCOMPARE(var, 413.994784025);
	} catch(std::exception& e) {
		qDebug() << e.what();
		QFAIL("Value-at-Risk should have been successfuly computed.");
	}
}

/**
 * @brief Tests VaR computation on monday. It implies to find out the last date to consider
 * for the returns which the previous friday
 */
void TestVaRHistorical::testExecuteOnMonday() {
	// Value-at-Risk parameters
	double risk = 0.20;
	int timeHorizon = 1;
	int returnsPeriod = 10;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		double var = daxVaR.execute(QDate(2014, 3, 10));
		// Compares the computed VaR matches with the manually found one
		QCOMPARE(var, 192.12);
	} catch(std::exception& e) {
		qDebug() << e.what();
		QFAIL("Value-at-Risk should have been successfuly computed.");
	}
}

/**
 * @brief Tests that VaR cannot be computed on weekends.
 */
void TestVaRHistorical::testExecuteOnWeekend() {
	// Value-at-Risk parameters
	double risk = 0.20;
	int timeHorizon = 1;
	int returnsPeriod = 10;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		daxVaR.execute(QDate(2014, 3, 8));
		QFAIL("Value-at-Risk should not have been computed on a weekend day.");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}

	try {
		daxVaR.execute(QDate(2014, 3, 9));
		QFAIL("Value-at-Risk should not have been computed on a weekend day.");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests the impossibilty to compute the Value-at-Risk at an undefined future date
 */
void TestVaRHistorical::testInvalidFutureDate() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 45;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		daxVaR.execute(QDate(2014, 3, 13));
		QFAIL("Computation of Value-at-Risk at an undefined future date");
	} catch(std::invalid_argument& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests the computation of the the Value-at-Risk at dates preceding the first
 * valid date (ie the third first day) and at the first valid day
 *
 */
void TestVaRHistorical::testInvalidPastDate() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 10;
	int returnsPeriod = 1;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		daxVaR.execute(QDate(2014, 1, 2));
		QFAIL("Computation of Value-at-Risk at an undefined past date");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}

	try {
		daxVaR.execute(QDate(2014, 1, 3));
		QFAIL("Computation of Value-at-Risk at an undefined past date");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests the computation of the the Value-at-Risk at the first valid day
 */
void TestVaRHistorical::testFirstValidDate() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 1;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		double var = daxVaR.execute(QDate(2014, 1, 6));
		QCOMPARE(var, 0.0); // Because the first and only return is positive, thus VaR is zero
	} catch(std::exception& e) {
		QFAIL("Value-at-Risk should have been successfuly computed.");
		qDebug() << e.what();
	}
}

/**
 * @brief Tests the impossibilty to compute the Value-at-Risk because there are not enough
 * portfolio values to satisfy the returnsPeriod parameter
 */
void TestVaRHistorical::testTooLargeReturnsPeriod() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 100;

	VaRHistorical incorrectDaxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);
	try {
		incorrectDaxVaR.execute(QDate(2014, 3, 12));
		QFAIL("execute() succeeded despite too large returnsPeriod parameter");

	} catch(std::range_error& e) {
		qDebug() << e.what();
	}
}

/**
 * @brief Tests if the Value-at-Risk is actually zero when there are only
 * positive returns
 */
void TestVaRHistorical::testExecuteNoNegativeReturns() {
	// Value-at-Risk parameters
	double risk = 0.05;
	int timeHorizon = 1;
	int returnsPeriod = 4;
	VaRHistorical daxVaR(this->daxPortfolio, risk, timeHorizon, returnsPeriod);

	try {
		double var = daxVaR.execute(QDate(2014, 2, 17));
		QCOMPARE(var, 0.0);
	} catch(std::exception &e) {
		qDebug() << e.what();
		QFAIL("Computation of Value-at-Risk failed");
	}
}
