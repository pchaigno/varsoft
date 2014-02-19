#include "VaRHistorical.h"

VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

double VaRHistorical::execute(QDateTime timeHorizon) const {
	// TODO
	return 0;
}
