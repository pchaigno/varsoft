#pragma once

#include "Portfolio.h"
#include <ctime>

class VaRAlgorithm {
private:
	const Portfolio& portfolio;
	double risk;

public:
	VaRAlgorithm(const Portfolio& portfolio, double risk);
	virtual double execute(time_t timeHorizon) const =0;
};