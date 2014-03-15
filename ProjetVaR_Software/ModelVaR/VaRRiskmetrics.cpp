#include "VaRRiskmetrics.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 */
VaRRiskmetrics::VaRRiskmetrics(const Portfolio& portfolio, double risk, int timeHorizon):
	VaRAlgorithm(portfolio, risk, timeHorizon) {

}

/**
 * @brief Computes the VaR using the Riskmetrics method.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using the Riskmetrics method.
 */
double VaRRiskmetrics::execute(QDateTime timeHorizon) const {
	// TODO
	return 0;
}
