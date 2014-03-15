#pragma once

#include <QtAlgorithms>
#include <QDateTime>
#include <QDebug>
#include <qmath.h>
#include "Portfolio.h"
#include "VaRAlgorithm.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT VaRHistorical: public VaRAlgorithm {
private:
	int period;
public:
	VaRHistorical(const Portfolio& portfolio, double risk, int timeHorizon, int period);
	virtual double execute(QDateTime date) const;
};
