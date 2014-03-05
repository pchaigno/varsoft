#pragma once

#include <QtAlgorithms>
#include <QDateTime>
#include "Portfolio.h"
#include "VaRAlgorithm.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT VaRHistorical: public VaRAlgorithm {
public:
	VaRHistorical(const Portfolio& portfolio, double risk);
    virtual double execute(int period) const;
};
