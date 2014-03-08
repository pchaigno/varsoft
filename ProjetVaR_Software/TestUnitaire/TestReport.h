#pragma once

#include "VaRReport.h"
#include "CorrelationReport.h"
#include "BacktestingReport.h"
#include "StatisticsReport.h"
#include "GarchReport.h"
#include <QtTest>

class TestReport: public QObject {
	Q_OBJECT

private:
	Report var;
	Report garch;
	Report correlation;
	Report statistics;
	Report backtesting;

public:
	TestReport();

private Q_SLOTS:
	void testId();
	void testId(Report report);
};
