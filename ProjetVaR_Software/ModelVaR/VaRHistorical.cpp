#include "VaRHistorical.h"

/**
 * @brief VaRHistorical::VaRHistorical
 * @param portfolio
 * @param risk
 */
VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {}

/**
 * @brief VaRHistorical::execute calculates the historical method based Value-at-Risk
 * @param period length of the period of time on which is defined the returns distribution
 * @return Value-at-Risk
 */
double VaRHistorical::execute(int period) const {
    QVector<double> returns;

    // Definitions of the starting and ending dates that define
    // the period of time on which return values are used to define
    // the returns distribution
    QDateTime endingPeriodDate = getPortfolio().retrieveLastDate();
    QDateTime startingPeriodDate = endingPeriodDate.addDays(-period+1);

    // If the distribution period is too large, then the corresponding starting date may not
    // be available in the database. A portfolioCalculationException will be thrown
    QVector<double> values = getPortfolio().getValues(startingPeriodDate, endingPeriodDate);

    // Returns have to be calculated first
    // TODO: Make it a function, it will most likely be reused somewhere else
    for(int i=1; i < values.size(); i++)
        returns.push_back(values.at(i) - values.at(i-1));

    // Return values are sorted
    qSort(returns.begin(), values.end());

    // Determine the worst return among the 100 - risk*100 percent of the best returns
    int quantile = getRisk()*returns.size();
    return returns.at(quantile);
}
