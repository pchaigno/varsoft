#pragma once

#include "VaRAlgorithm.h"
#include "GarchModel.h"
#include <QDateTime>

class VaRGarch: public VaRAlgorithm {
private:
	const GarchModel& garchModel;

public:
	VaRGarch(const Portfolio& portfolio, double risk, int timeHorizon, const GarchModel& garchModel);
	virtual double execute(QDateTime timeHorizon) const;
};
