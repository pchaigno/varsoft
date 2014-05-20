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
double VaRHistorical::execute(QDate date) const {
	// Makes it impossible to compute VaR on weekends
	if(date.dayOfWeek() >= 6) {
		throw std::invalid_argument("Value-at-Risk cannot be computed on weekends.");
	}

	// Finds out the date to be used with retrievesReturns
	QDate lastDate;
	// VaR computation on Tuesdays to fridays
	if(date.dayOfWeek() >= 2) {
		if(getPortfolio().retrieveEndDate().daysTo(date) > 1) {
			throw std::invalid_argument("The Value-at-Risk cannot be computed at an undefined future date.");
		}
		lastDate = date.addDays(-1);
	} else { // date.dayOfWeek() == 1 // VaR computation on monday
		if(getPortfolio().retrieveEndDate().daysTo(date) > 3) { // Period over the weekend
			throw std::invalid_argument("The Value-at-Risk cannot be computed at an undefined future date.");
		}
		lastDate = date.addDays(-3);
	}

	// Makes sure the last date is compatible with the portfolio start date
	if(lastDate <= getPortfolio().retrieveStartDate()) {
		throw std::invalid_argument("The Value-at-Risk cannot be computed at such an early date such as there are no returns.");
	}

	QVector<double> returns = getPortfolio().retrieveReturns(lastDate, period);
	// Makes sure the number of returns is satisfied
	if(returns.size() < period) {
		throw std::range_error("There are not enough portfolio values to satisfy the period parameter.");
	}

	// Return values are sorted
	qSort(returns.begin(), returns.end());

	// Determine the index of the risk-order quantile
	// floor() is used to round down the index in case of non integer result
	int quantileIndex = floor(getRisk()*returns.size())-1;
	// Prevents the index from being negative in small returns size of risk cases
	if(quantileIndex < 0) {
		quantileIndex = 0;
	}

	// The VaR is the opposite of the considered return (risk-order quantile)
	double quantile = returns.at(quantileIndex);
	double var;
	if(quantile >= 0) { // By definition, the VaR equals zero if the considered return is positive
		var = 0;
	} else if(getTimeHorizon() > 1) { // Takes into account the time horizon
		var = -quantile*qSqrt(getTimeHorizon());
	} else {
		var = -quantile;
	}

	// For future use
	// VaRReportFactory report(getPortfolio(), getRisk(), getTimeHorizon(), period, date, var);
	// report.generate();

	return var;
}
