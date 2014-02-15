#pragma once

#include "Portfolio.h"
#include <ctime>
#include "VaRAlgorithm.h"
#include <tuple>

class Backtesting {
private:
	const Portfolio& portfolio;
	const VaRAlgorithm& varAlgo;
	const tuple<time_t>& backtestperiod;

public:
	Backtesting(const Portfolio& portfolio, const VaRAlgorithm& varAlgo, const tuple<time_t>& backtestperiod);
	int compute() const;
};