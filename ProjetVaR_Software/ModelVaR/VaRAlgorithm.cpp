#include "VaRAlgorithm.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 */
VaRAlgorithm::VaRAlgorithm(const Portfolio& portfolio, double risk): portfolio(portfolio) {
	this->risk = risk;
}

const Portfolio &VaRAlgorithm::getPortfolio() const {
    return this->portfolio;
}

double VaRAlgorithm::getRisk() const {
    return this->risk;
}
