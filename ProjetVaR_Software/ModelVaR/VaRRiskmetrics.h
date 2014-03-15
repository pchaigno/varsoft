#pragma once

#include "VaRAlgorithm.h"
#include <QDateTime>

class VaRRiskmetrics: public VaRAlgorithm {
public:
	VaRRiskmetrics(const Portfolio& portfolio, double risk, int timeHorizon);
	virtual double execute(QDateTime timeHorizon) const;
};
