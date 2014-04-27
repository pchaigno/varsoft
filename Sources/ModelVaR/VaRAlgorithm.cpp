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
