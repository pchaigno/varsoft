#pragma once

#include "ModelVaR_global.h"
#include "Portfolio.h"
#include <ctime>

class MODELVARSHARED_EXPORT VaRAlgorithm {
private:
	const Portfolio& portfolio;
	double risk;

public:
	VaRAlgorithm(const Portfolio& portfolio, double risk);
    virtual double execute(QDateTime timeHorizon) const =0;
    const Portfolio& getPortfolio() const;
    double getRisk() const;
};
