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
#include "VaRGarch.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 * @param garchModel The GARCH model estimated from the portfolio.
 */
VaRGarch::VaRGarch(const Portfolio& portfolio, double risk, int timeHorizon, const GarchModel& garchModel, int nbScenarios, bool initStddev, int initPeriod):
	VaRAlgorithm(portfolio, risk, timeHorizon), garchModel(garchModel), nbScenarios(nbScenarios), initStddev(initStddev), initPeriod(initPeriod) {
}

/**
 * @brief Computes the VaR using the GARCH model.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using a GARCH model.
 */
double VaRGarch::execute(QDateTime date) const {
	double var;
	QVector<double> residuals;

	bool debug = true;

	// Retrieves model coefficients and residuals for VaR computation
	double omega = garchModel.getOmega();
	double alpha = garchModel.getAlpha();
	double beta = garchModel.getBeta();
	residuals = garchModel.getResiduals();




	// Initialization of stddev
	double stddev;
	if(initStddev) {
		QVector<double> returns = portfolio.retrieveLogReturns(date, initPeriod);
		qDebug() << "returns.size()";
		qDebug() << returns.size();
		stddev = 0;
		qDebug() << "DEBUT";
		for(int i=0; i < returns.size()-1; i++) {
			qDebug() << stddev;
			stddev = qSqrt(omega + alpha*qPow(returns.at(i), 2) + beta*qPow(stddev, 2));
		}
	} else {
		stddev = garchModel.getStddev();
	}

	qDebug() << "In VaR Garch";
	qDebug() << "residuals";
	qDebug() << residuals;
	qDebug() << "stddev";
	qDebug() << stddev;


	// Create seed for the random
	// The following makes sure it is executed only once
	static bool initialized;
	if (!initialized) {
	   initialized = true;
	   QTime time = QTime::currentTime();
	   qsrand((uint)time.msec());
	}

	QVector<double> generatedReturns;
	// Boostrap process
	for(int i=0; i < nbScenarios; i++) {
		// Initialization with the latest real values
		double previousReturn = portfolio.retrieveLogReturns(date, 1).at(0);
		double previousStddev = stddev;
		double horizonReturn = 0;
		for(int h=0; h < timeHorizon; h++) {
			// Draw with replacement of a residual
			int randomIndex = qrand() % residuals.size();
			double sigmaSquared = omega + alpha*qPow(previousReturn, 2) + beta*qPow(previousStddev, 2);
			double partialReturn = qSqrt(sigmaSquared)*residuals.at(randomIndex);
			horizonReturn += partialReturn;
			// Initialization for the next iteration
			previousReturn = partialReturn;
			previousStddev = qSqrt(sigmaSquared);
		}
		generatedReturns.push_back(horizonReturn);
	}

	// Return values are sorted
	qSort(generatedReturns.begin(), generatedReturns.end());

	if(debug) {
		qDebug() << "Sorted generatedReturns";
		qDebug() << generatedReturns;
	}

	// Vector quantile calculation
	// Using floor(), we expect the worst case
	int quantile = floor(getRisk()*generatedReturns.size()-1);
	if(debug) {
		qDebug() << "quantile";
		qDebug() << quantile;
		qDebug() << generatedReturns.at(quantile);
		qDebug() << "Latest value:";
		qDebug() << getPortfolio().retrieveValues(date, date).at(0);
	}
	var = (1 - qExp(generatedReturns.at(quantile)))*getPortfolio().retrieveValues(date, date).at(0);

	return var;
}
