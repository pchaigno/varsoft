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

#include <QtTest>
#include "Portfolio.h"
#include "math/Backtesting.h"
#include "math/VaRHistorical.h"
#include "math/VaRRiskmetrics.h"

class TestBacktesting: public QObject {
	Q_OBJECT

private:
	Portfolio* portfolio;

public:
	TestBacktesting();

private Q_SLOTS:
	void testBacktestingHistorical();
	void testBacktestingRiskmetrics();
	void testBacktestingIncorrect1();
	void testBacktestingIncorrect2();
	void testBacktestingIncorrect3();
};
