#include "VaRHistorical.h"

VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

double VaRHistorical::execute(int period) const {

    QDateTime endingPeriodDate = portfolio.retrieveLastDate();
    QDateTime startingPeriodDate = lastDate.addDays(-period+1);
    QVector<double> values = portfolio.getAsQVectors(startingPeriodDate, endingPeriodDate);

    if(startingPeriodDate < portfolio.retrieveFirstDate()) {
        // Couille dans le piano
    }

    // Utilise qsort
    values.

	return 0;
}
