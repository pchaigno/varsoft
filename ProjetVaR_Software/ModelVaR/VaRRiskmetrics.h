#pragma once

#include "VaRAlgorithm.h"

class VaRRiskmetrics: public VaRAlgorithm {
public:
	VaRRiskmetrics(const Portfolio& portfolio, double risk);
	virtual double execute(time_t timeHorizon) const;
};