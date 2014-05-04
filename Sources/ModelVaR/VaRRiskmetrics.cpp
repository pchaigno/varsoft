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
#include "VaRRiskmetrics.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 * @param timeHorizon the time of horizon of the computed VaR in number of days
 * @param initPeriod The initialization period using previous returns for the VaR computation in number of days
 */
VaRRiskmetrics::VaRRiskmetrics(const Portfolio& portfolio, double risk, int timeHorizon, int initPeriod):
	VaRAlgorithm(portfolio, risk, timeHorizon), initPeriod(initPeriod) {

	if(initPeriod <= 0) {
		throw std::invalid_argument("The initPeriod argument must be strictly positive");
	}
}

/**
 * @brief Computes the VaR using the Riskmetrics method.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using the Riskmetrics method.
 */
double VaRRiskmetrics::execute(QDate date) const {

	// Computes Sigma value using historical log-returns
	QVector<double> logReturns = this->getPortfolio().retrieveLogReturns(date, initPeriod);
	double sigmaSquarred = 0;
	for(int i=0; i < logReturns.size(); i++) {
		sigmaSquarred = 0.94*sigmaSquarred + 0.06*qPow(logReturns.at(i), 2);
	}

	// Computes 1-day time horizon VaR
	double var = this->getPortfolio().retrieveValues(date, date).at(0)*qSqrt(sigmaSquarred)*MathFunctions::normalCDFInverse(1.0-getRisk());

	// Adjusts VaR according to the time horizon
	if(getTimeHorizon() >= 2) {
		var *= qSqrt(getTimeHorizon());
	}

	return var;
}
