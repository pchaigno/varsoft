#pragma once

#include "VaRAlgorithm.h"
#include <QDateTime>

class VaRRiskmetrics: public VaRAlgorithm {
public:
	VaRRiskmetrics(const Portfolio& portfolio, double risk);
	virtual double execute(QDateTime timeHorizon) const;
};