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

	returns = getPortfolio().retrieveReturns(getPortfolio().retrieveLastDate(), period);

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
