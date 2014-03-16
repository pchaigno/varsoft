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
	double var;
	QVector<double> returns;

	// Definitions of the starting that define with the passed date
	// the period of time on which return values are used
	// PB when market closed
	// Additionnal getter needs to be written
	QDateTime endingPeriodDate = date;
	QDateTime startingPeriodDate = endingPeriodDate.addDays(-period+1);

	// If the distribution period is too large, then the corresponding starting date may not
	// be available in the database. A portfolioCalculationException will be thrown
	QVector<double> values = getPortfolio().getValues(startingPeriodDate, endingPeriodDate);

	// Make sure there is there is the exact number of returns
	while(values.size() < period) {
		startingPeriodDate.addDays(-1);
		values.push_front(getPortfolio().getValues(startingPeriodDate, startingPeriodDate).at(0));
	}

	// Returns have to be calculated first
	returns = Portfolio::getReturns(values);

	// Return values are sorted
	qSort(returns.begin(), returns.end());

	// Determine the best return of the risk*100 % worst returns
	int quantile = getRisk()*returns.size();

	// Take into account the time horizon
	var = returns.at(quantile)*qSqrt(getTimeHorizon());

	// For future use
	// VaRReportFactory report(getPortfolio(), getRisk(), getTimeHorizon(), period, date, var);
	// report.generate();

	return var;
}
