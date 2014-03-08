#pragma once

#include "VaRAlgorithm.h"
#include "GarchModel.h"
#include <QDateTime>

class VaRGarch: public VaRAlgorithm {
private:
	const GarchModel& garchModel;

public:
	VaRGarch(const Portfolio& portfolio, double risk, const GarchModel& garchModel);
	virtual double execute(QDateTime timeHorizon) const;
};
