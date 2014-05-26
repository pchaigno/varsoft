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

#include <QString>
#include <QPair>
#include <QList>
#include <QDate>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT CorrelationResults{

public:
	CorrelationResults(QString s, double st_v, double p_v, int lag, int per, QString d);
	~CorrelationResults();
	QString getType() const;
	double getStatValue() const;
	double getPValue() const;
	int getTimeLag() const;
	int getPeriod() const;
	QString getDate() const;
private:
	QString testType;
	double statValue;
	double pValue;
	int timeLag;
	int period;
	QString date;
};

