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
 * @param nbInitIterations number of iterations to perform to initialize the first standard deviation value
 */
VaRGarch::VaRGarch(const Portfolio& portfolio, double risk, int timeHorizon, const GarchModel& garchModel, int nbScenarios, int nbInitIterations):
	VaRAlgorithm(portfolio, risk, timeHorizon), garchModel(garchModel), nbScenarios(nbScenarios), nbInitIterations(nbInitIterations) {

	if(nbScenarios < 1) {
		throw std::invalid_argument("There must be at least one scenario for the VaR computation");
	}
	if(nbInitIterations) {
		if(nbInitIterations < 2) {
			throw std::invalid_argument("The number of iterations to initialize the standard deviation must be greater than one");
		}
	}
}

/**
 * @brief Computes the VaR using the GARCH model.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using a GARCH model.
 */
double VaRGarch::execute(QDate date) const {
	// Makes sure the date is valid and gets the appropriate date to perform computations
	QDate lastDate = checkDate(date);

	// Retrieves model coefficients and residuals for VaR computation
	double omega = garchModel.getOmega();
	double alpha = garchModel.getAlpha();
	double beta = garchModel.getBeta();
	QVector<double> residuals = garchModel.getResiduals();

	// Initializes stddev using the previous returns
	double stddev = 0;
	QVector<double> returns = portfolio.retrieveLogReturns(lastDate, nbInitIterations);
	for(int i=0; i < returns.size()-1; i++) {
		stddev = qSqrt(omega + alpha*qPow(returns.at(i), 2) + beta*qPow(stddev, 2));
	}

	// Create seed for the random draw during the bootsrap
	// Makes sure it is executed only once
	static bool initialized;
	if (!initialized) {
	   initialized = true;
	   QTime time = QTime::currentTime();
	   qsrand((uint)time.msec());
	}

	QVector<double> generatedReturns;
	// Boostrap process : computes nbScenarios possible returns (time horizon taken into account)
	for(int i=0; i < nbScenarios; i++) {
		// Initialization with the latest real values
		double previousReturn = portfolio.retrieveLogReturns(lastDate, 1).first();
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
	int quantile = floor(getRisk()*generatedReturns.size())-1;
	// Prevents the index from being negative in small returns size of risk cases
	if(quantile < 0) {
		quantile = 0;
	}

	// Calculates VaR according to the formula
	double var = (1 - qExp(generatedReturns.at(quantile)))*getPortfolio().retrieveValues(lastDate, lastDate).first();

	// If the VaR is negative, we return 0 in such cases according to the VaR definition
	if(var < 0) {
		var = 0;
	}

	return var;
}


void VaRGarch::setParamJson(ReportDataJson * data)
{
	QList<QMap<QString,QString> > listParam;

	QMap<QString,QString> param;
	param["Title"]="Number of scenario";
	param["Value"]=nbScenarios;
	listParam.append(param);

	QMap<QString,QString> param2;
	param2["Title"]="Number of iteration";
	param2["Value"]=nbInitIterations;
	listParam.append(param2);

	data->addList("params",listParam);
}

QString VaRGarch::getNameMethod()
{
	return "GARCH method";
}

int VaRGarch::getEnumMethod()
{
	return GARCHMETHOD;
}
