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
		throw std::invalid_argument("The period argument must be strictly positive, passed value: "+period);
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
	QVector<double> returns;

	// Check date makes sense

	// Definitions of the starting that define with the passed date
	// the period of time on which return values are used
	// PB when market closed
	QDateTime endingPeriodDate = date;
	QDateTime startingPeriodDate = endingPeriodDate.addDays(-period+1);

	// If the distribution period is too large, then the corresponding starting date may not
	// be available in the database. A portfolioCalculationException will be thrown
	QVector<double> values = getPortfolio().getValues(startingPeriodDate, endingPeriodDate);

	// Returns have to be calculated first
	// TODO: Make it a function, it will most likely be reused somewhere else
	for(int i=1; i < values.size(); i++)
		returns.push_back(values.at(i) - values.at(i-1));

	// Return values are sorted
	qSort(returns.begin(), returns.end());

	// Determine the best return of the risk*100 % worst returns
	int quantile = getRisk()*returns.size();

	// Take into account the time horizon
	return returns.at(quantile)*qSqrt(getTimeHorizon());
}
