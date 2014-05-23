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
#include "VaRAlgorithm.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 * @param timeHorizon The time horizon in number of days
 */
VaRAlgorithm::VaRAlgorithm(const Portfolio& portfolio, double risk, int timeHorizon): portfolio(portfolio) {
	if(risk <= 0 || risk >= 1) {
		throw std::invalid_argument("The risk parameter must lie within the 0..1 interval, excluding the limits");
	} else {
		this->risk = risk;
	}

	if(timeHorizon <= 0) {
		throw std::invalid_argument("timeHorizon parameter must be strictly positive");
	} else {
		this->timeHorizon = timeHorizon;
	}
}

/**
 * @brief Accessor to the portfolio
 * @return the portfolio associated with the Value-at-Risk calculation
 */
const Portfolio &VaRAlgorithm::getPortfolio() const {
	return this->portfolio;
}

/**
 * @brief Accessor to the risk
 * @return the risk associated with the Value-at-Risk calculation
 */
double VaRAlgorithm::getRisk() const {
	return this->risk;
}

/**
 * @brief Accessor to the time horizon
 * @return the time horizon in number of days associated with the Value-at-Risk calculation
 */
int VaRAlgorithm::getTimeHorizon() const {
	return this->timeHorizon;
}

/**
 * @brief Checks the date is valied to perform the Value-at-Risk computation. Returns the
 * date to use with retrievers to perform actual computation
 * @param date The date at which the Value-at-Risk is computed
 * @return The date the retrievers must use to perform the given Value-at-Risk computation
 */
QDate VaRAlgorithm::checkDate(QDate date) const {
	// Makes it impossible to compute VaR on weekends
	if(date.dayOfWeek() >= 6) {
		throw std::invalid_argument("Value-at-Risk cannot be computed on weekends.");
	}

	// Finds out the date to be used with retrievesReturns and checks it is compatible with the
	// portfolio endate
	QDate lastDate;
	// VaR computation on Tuesdays to fridays
	if(date.dayOfWeek() >= 2) {
		if(this->getPortfolio().retrieveEndDate().daysTo(date) > 1) {
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

	return lastDate;
}
