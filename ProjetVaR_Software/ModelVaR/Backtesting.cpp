#include "Backtesting.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio on which we want to run the test.
 * @param varAlgo The algorithm to compute the Value-at-Risk.
 * @param backtestperiod The time period of backtesting.
 */
Backtesting::Backtesting(const Portfolio& portfolio, const VaRAlgorithm& varAlgo, const tuple<time_t>& backtestperiod):
	portfolio(portfolio), varAlgo(varAlgo), backtestperiod(backtestperiod) {

}

/**
 * @brief Compute the backtesting.
 * @return The number of day for which the VaR is above what it should be.
 */
int Backtesting::compute() const {
	// TODO
	return 0;
}