/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
