#include "VaRHistorical.h"

VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

/**
 * @brief VaRHistorical::execute
 * @param period
 * @return
 */
double VaRHistorical::execute(int period) const {

    QDateTime endingPeriodDate = getPortfolio().retrieveLastDate();
    QDateTime startingPeriodDate = endingPeriodDate.addDays(-period+1);
    QVector<double> values = getPortfolio().getValues(startingPeriodDate, endingPeriodDate);

    if(startingPeriodDate < getPortfolio().retrieveFirstDate()) {
        // Couille dans le piano
    }

    // Utilise qsort
    //values.

    qSort(values.begin(), values.end());

    int quantile = risk*values.size();
    return values.at();
}
