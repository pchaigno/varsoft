#include "VaRAlgorithm.h"

VaRAlgorithm::VaRAlgorithm(const Portfolio& portfolio, double risk): portfolio(portfolio) {
	this->risk = risk;
}
