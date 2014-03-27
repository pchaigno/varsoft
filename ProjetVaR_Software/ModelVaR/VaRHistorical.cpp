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
#include "VaRHistorical.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 * @param timeHorizon the time horizon of the Value-at-Risk
 * @param period Period length of returns to calculate the Value-at-Risk
 */
VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk, int timeHorizon, int period):
	VaRAlgorithm(portfolio, risk, timeHorizon) {

	if(period <= 0) {
		throw std::invalid_argument("The period argument must be strictly positive");
	} else {
		this->period = period;
	}
}

/**
 * @brief Calculates the historical method based Value-at-Risk
 * @param date Date on which the Value-at-Risk is calculated
 * @return Value-at-Risk
 */
double VaRHistorical::execute(QDateTime date) const {
	double var;
	QVector<double> returns;

	returns = getPortfolio().retrieveReturns(date, period);

	if(returns.size() < period) {
		throw std::range_error("Not enough portfolio values to satisfy the period parameter");
	}

	// Return values are sorted
	qSort(returns.begin(), returns.end());

	// Determine the best return of the risk*100 % worst returns
	// Using floor(), we expect the worst case
	int quantile = floor(getRisk()*returns.size()-1);

	// Take into account the time horizon
	var = returns.at(quantile)*qSqrt(getTimeHorizon());

	// For future use
	// VaRReportFactory report(getPortfolio(), getRisk(), getTimeHorizon(), period, date, var);
	// report.generate();

	return var;
}
