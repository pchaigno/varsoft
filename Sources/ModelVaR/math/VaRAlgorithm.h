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

#include "ModelVaR_global.h"
#include "Portfolio.h"
#include <stdexcept>
#include <ctime>
#include <QDebug>
#include "report/ReportDataJson.h"


#define HISTORICAL 0
#define RISKMETRICS 1
#define GARCHMETHOD 2

class MODELVARSHARED_EXPORT VaRAlgorithm {
protected:
	const Portfolio& portfolio;
	double risk;
	int timeHorizon;


public:
	virtual void setParamJson(ReportDataJson*) = 0;
	virtual QString getNameMethod()= 0;
	virtual int getEnumMethod() = 0;
	VaRAlgorithm(const Portfolio& portfolio, double risk, int timeHorizon);
	virtual double execute(QDate date) const =0;

	const Portfolio& getPortfolio() const;
	double getRisk() const;
	int getTimeHorizon() const;
	QDate checkDate(QDate date) const;
};
