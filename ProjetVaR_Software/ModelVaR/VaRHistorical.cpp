#include "VaRHistorical.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 */
VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

/**
 * @brief Computes the VaR using the historical method.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using the historical method.
 */
double VaRHistorical::execute(QDateTime timeHorizon) const {
	// TODO
	return 0;
}
