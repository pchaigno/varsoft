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

#include "Portfolio.h"
#include <QtTest>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QVector>
#include "Asset.h"

class TestPortfolio: public QObject {
	Q_OBJECT

private:
	Portfolio* father;
	Portfolio* son;
	Portfolio* uncle;
	Portfolio* auntie;
	Portfolio* weekends;

public:
	TestPortfolio();

private Q_SLOTS:
	void testId();
	void testName();
	void testRetrieveStartDate();
	void testRetrieveEndDate();
	void testRetrieveValues();
	void testRetrieveValuesWeekends();
	void testRetrieveValuesByDate();
	void testRetrieveValuesByDateMissingValues();
	void testRetrieveValuesNoParameters();
	void testRetrieveReturns();
	void testRetrieveNbReturnsNotEnough();
	void testRetrieveNbReturnsAll();
	void testRetrieveNbReturnsSome();
	void testRetrieveReturnHorizon();
	void testRetrieveReturnHorizonIncorrect();
};
