#pragma once

#include "Portfolio.h"
#include "VaRAlgorithm.h"
#include <QPair>
#include <QDateTime>
#include <QPair>

class Backtesting {
private:
	const Portfolio& portfolio;
	const VaRAlgorithm& varAlgo;
	const QPair<QDateTime, QDateTime>& backtestperiod;

public:
	Backtesting(const Portfolio& portfolio, const VaRAlgorithm& varAlgo, const QPair<QDateTime, QDateTime>& backtestperiod);
	int compute() const;
};
