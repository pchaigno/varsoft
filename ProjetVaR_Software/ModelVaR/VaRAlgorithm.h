#pragma once

#include "ModelVaR_global.h"
#include "Portfolio.h"
#include <stdexcept>
#include <ctime>

class MODELVARSHARED_EXPORT VaRAlgorithm {
private:
	const Portfolio& portfolio;
	double risk;
	int timeHorizon;

public:
	VaRAlgorithm(const Portfolio& portfolio, double risk, int timeHorizon);
	virtual double execute(QDateTime date) const =0;
    const Portfolio& getPortfolio() const;
    double getRisk() const;
	double getTimeHorizon() const;
};
