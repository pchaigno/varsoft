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
VaRGarch::VaRGarch(const Portfolio& portfolio, double risk, int timeHorizon, const GarchModel& garchModel, int nbScenarios):
	VaRAlgorithm(portfolio, risk, timeHorizon), garchModel(garchModel), nbScenarios(nbScenarios) {

}

/**
 * @brief Computes the VaR using the GARCH model.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using a GARCH model.
 */
double VaRGarch::execute(QDateTime date) const {
	double var;
	QVector<double> residuals, stddev, logReturns;

	// It only needs the latest return
	logReturns = portfolio.retrieveLogReturns(date, 1);
	qDebug() << logReturns;

	// Retrieves model coefficients for following computation
	double omega = garchModel.getOmega();
	double alpha = garchModel.getAlpha();
	double beta = garchModel.getBeta();

	//	residuals = garchModel.getResiduals();
	//	stddev = garchModel.getStddev();

	// Create seed for the random
	// That is needed only once on application startup
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	QVector<double> futurReturns;
	// Deboostrap process

	for(int i = 0; i < nbScenarios; i++) {
		double sigmaSquareFutur = omega + alpha*qPow(logReturns.last(), 2) + beta*qPow(stddev.last(), 2);
		double futurReturnSum = 0;
		for(int h=0; h < timeHorizon; h++) {
			// Draw with replacement of a residual
			int randomIndex = qrand() % residuals.size();
			double futurReturn = (qSqrt(sigmaSquareFutur)*residuals.at(randomIndex));
			futurReturnSum += futurReturn;
			sigmaSquareFutur = omega + alpha*qPow(futurReturn, 2) + beta*qPow(sigmaSquareFutur, 2);
		}
		futurReturns.push_back(futurReturnSum);
	}

	// Return values are sorted
	qSort(futurReturns.begin(), futurReturns.end());

	// Determine the best return of the risk*100 % worst returns
	// Using floor(), we expect the worst case
	int quantile = floor(getRisk()*futurReturns.size()-1);
	var = (1 - qExp(futurReturns.at(quantile)))*getPortfolio().retrieveValues(date, date).at(0);

	return var;
}
