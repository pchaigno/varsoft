#include "VaRHistorical.h"

/**
 * @brief VaRHistorical::VaRHistorical
 * @param portfolio
 * @param risk
 */
VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {}

/**
 * @brief VaRHistorical::execute
 * @param period Period of the time on which returns define the distribution returns
 * @return Value-at-Risk given the parameters
 */
double VaRHistorical::execute(int period) const {

    // Definitions of the starting and ending dates that define
    // the period of time on which return values are used to define
    // the returns distribution
    QDateTime endingPeriodDate = getPortfolio().retrieveLastDate();
    QDateTime startingPeriodDate = endingPeriodDate.addDays(-period+1);

    QVector<double> values = getPortfolio().getValues(startingPeriodDate, endingPeriodDate);

    // If the distribution period is too large, then the corresponding starting date may not
    // be available in the database
    if(startingPeriodDate < getPortfolio().retrieveFirstDate()) {
        // TODO: create specific exception
    }

    // Returns have to calculated


    // Return values are sorted
    qSort(values.begin(), values.end());

    // FAUX
    int quantile = getRisk()*values.size();
    return values.at(quantile);
}
