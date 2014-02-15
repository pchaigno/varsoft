#include "VaRHistorical.h"

VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

double VaRHistorical::execute(time_t timeHorizon) const {
	// TODO
	return 0;
}