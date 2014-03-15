#include "VaRAlgorithm.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 * @param timeHorizon The time horizon in number of days
 */
VaRAlgorithm::VaRAlgorithm(const Portfolio& portfolio, double risk, int timeHorizon): portfolio(portfolio) {
	if(risk <= 0 || risk >= 1) {
		throw std::invalid_argument("The risk parameter must lie within the 0..1 interval, excluding the limits");
	} else {
		this->risk = risk;
	}

	if(timeHorizon <= 0) {
		throw std::invalid_argument("timeHorizon parameter must be strictly positive");
	} else {
		this->timeHorizon = timeHorizon;
	}
}

/**
 * @brief Accessor to the portfolio
 * @return the portfolio associated with the Value-at-Risk calculation
 */
const Portfolio &VaRAlgorithm::getPortfolio() const {
    return this->portfolio;
}

/**
 * @brief Accessor to the risk
 * @return the risk associated with the Value-at-Risk calculation
 */
double VaRAlgorithm::getRisk() const {
    return this->risk;
}

/**
 * @brief Accessor to the time horizon
 * @return the time horizon associated with the Value-at-Risk calculation
 */
double VaRAlgorithm::getTimeHorizon() const {
	return this->timeHorizon;
}
