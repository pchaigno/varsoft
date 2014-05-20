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
#include "Backtesting.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio on which we want to run the test.
 * @param varAlgo The algorithm to compute the Value-at-Risk.
 * @param backtestperiod The time period of backtesting.
 */
Backtesting::Backtesting(const Portfolio& portfolio, const VaRAlgorithm& varAlgo, const QPair<QDate, QDate> &backtestperiod):
	portfolio(portfolio), varAlgo(varAlgo), backtestperiod(backtestperiod) {

}

/**
 * @brief Compute the backtesting.
 * @return The number of day for which the VaR is above what it should be.
 */
int Backtesting::compute() const {
	int nbDaysLossGreaterThanVaR = 0;

	for(QDate date=QDate(backtestperiod.first); date <= backtestperiod.second; date=date.addDays(1)) {
		if(date.dayOfWeek()<=5) { // Backtests only on week days
			double var = varAlgo.execute(date);
			if(portfolio.retrieveReturnHorizon(date, varAlgo.getTimeHorizon()) > -var) {
				nbDaysLossGreaterThanVaR++;
			}
		}
	}

	return nbDaysLossGreaterThanVaR;
}
