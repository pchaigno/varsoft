#include "VaRGarch.h"

VaRGarch::VaRGarch(const Portfolio& portfolio, double risk, const GarchModel& garchModel):
	VaRAlgorithm(portfolio, risk), garchModel(garchModel) {

}

double VaRGarch::execute(time_t timeHorizon) const {
	// TODO
	return (double)timeHorizon;
}