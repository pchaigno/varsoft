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

	if(backtestperiod.first <= portfolio.retrieveStartDate()) {
		throw std::invalid_argument("The backtesting cannot be performed before the portfolio start date or at the start date itself.");
	}

	if(backtestperiod.second > portfolio.retrieveEndDate().addDays(-varAlgo.getTimeHorizon()+1)) {
		throw std::invalid_argument("The backtesting cannot be performed after the portfolio end date. This may be because of a too large time horizon regarding the period end date.");
	}

}

/**
 * @brief Computes the backtesting i.e. computes the Value-at-Risk every week day
 * of the backtesting period. Counts the number of times the actual return is worse
 * than the Value-at-Risk
 * @return The number of day for which the loss is greater than the VaR
 */
int Backtesting::compute() const {
	int nbDaysLossGreaterThanVaR = 0;

	for(QDate date=QDate(backtestperiod.first); date <= backtestperiod.second; date=date.addDays(1)) {
		if(date.dayOfWeek()<=5) { // Backtests only on week days
			double var = varAlgo.execute(date);
			// Compares the VaR to the actual return (taking into account the horizon)
			if(portfolio.retrieveReturnHorizon(date, varAlgo.getTimeHorizon()) < -var) {
				nbDaysLossGreaterThanVaR++;
			}
		}
	}

//	ReportFactory * factory = new BacktestingReportFactory(this);
//	Report * report = factory->buildReport();
//	ReportGenerator * generator = new DocxGenerator(report, "C:/Users/Ulysse/ProjetVaR/DocxGenerator/DocXGenerator.jar");
//	generator->start();

	return nbDaysLossGreaterThanVaR;
}

void Backtesting::run()
{
	compute();
}
