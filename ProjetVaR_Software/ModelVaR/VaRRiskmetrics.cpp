#include "VaRRiskmetrics.h"

VaRRiskmetrics::VaRRiskmetrics(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

double VaRRiskmetrics::execute(QDateTime timeHorizon) const {
	// TODO
	return 0;
}