#pragma once

#include "VaRAlgorithm.h"

class VaRHistorical: public VaRAlgorithm {
public:
	VaRHistorical(const Portfolio& portfolio, double risk);
    virtual double execute(QDateTime timeHorizon) const;
};