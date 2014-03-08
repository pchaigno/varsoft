#include "VaRGarch.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 * @param garchModel The GARCH model estimated from the portfolio.
 */
VaRGarch::VaRGarch(const Portfolio& portfolio, double risk, const GarchModel& garchModel):
	VaRAlgorithm(portfolio, risk), garchModel(garchModel) {

}

/**
 * @brief Computes the VaR using the GARCH model.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using a GARCH model.
 */
double VaRGarch::execute(QDateTime timeHorizon) const {
	// TODO
	return (double)timeHorizon.toTime_t();
}
