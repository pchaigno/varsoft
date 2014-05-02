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
 * @param timeHorizon the time horizon of the VaR in number of days.
 * @param garchModel The GARCH model estimated from the portfolio.
 * @param nbScenarios The number of scenarios to perform the bootstrap process
 * @param initStddev indicates if the first standard value should computed from historical returns
 * or the one included in the model should be used. Useful for the backtesting to not compute a Garch
 * model for every daylight
 * @param initPeriod number of returns to use to initialize the first standard deviation value
 */
VaRGarch::VaRGarch(const Portfolio& portfolio, double risk, int timeHorizon, const GarchModel& garchModel, int nbScenarios, bool initStddev, int initPeriod):
	VaRAlgorithm(portfolio, risk, timeHorizon), garchModel(garchModel), nbScenarios(nbScenarios), initStddev(initStddev), initPeriod(initPeriod) {

	if(nbScenarios < 1) {
		throw std::invalid_argument("There must be at least one scenario for the VaR computation");
	}
	if(initPeriod) {
		if(initPeriod < 2) {
			throw std::invalid_argument("The initialization period must greater than two");
		}
	}
}

/**
 * @brief Computes the VaR using the GARCH model.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using a GARCH model.
 */
double VaRGarch::execute(QDate date) const {

	// Retrieves model coefficients and residuals for VaR computation
	double omega = garchModel.getOmega();
	double alpha = garchModel.getAlpha();
	double beta = garchModel.getBeta();
	QVector<double> residuals = garchModel.getResiduals();

	// Initialization of the last standard deviation value, stddev
	double stddev;
	if(initStddev) {
		// Initializes stddev using the previous returns
		QVector<double> returns = portfolio.retrieveLogReturns(date, initPeriod);
		stddev = 0;
		for(int i=0; i < returns.size()-1; i++) {
			stddev = qSqrt(omega + alpha*qPow(returns.at(i), 2) + beta*qPow(stddev, 2));
		}
	} else {
		// Initializes stddev to the model value
		stddev = garchModel.getStddev();
	}

	qDebug() << stddev;

	// Create seed for the random draw
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

	// Vector quantile calculation
	// Using floor(), we expect the worst case
	int quantile = floor(getRisk()*generatedReturns.size()-1);

	double var = (1 - qExp(generatedReturns.at(quantile)))*getPortfolio().retrieveValues(date, date).at(0);

	// There may be cases when the var is negative, we return 0 in such cases according to the VaR formula
	if(var < 0) {
		var = 0;
	}

	return var;
}
