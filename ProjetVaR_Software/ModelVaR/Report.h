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
#include "IdAlreadyAttributedException.h"
#include "ModelVaR_global.h"
#include "ReportDataJson.h"

enum ReportType {
	NONE = 0,
	BACKTESTING,
	CORRELATION,
	GARCH,
	STATISTICS,
	VAR
};

class MODELVARSHARED_EXPORT Report {
private:
    int id;
    QString file;
    ReportDataJson* dataJson;

public:
    Report();
    Report(QString file);
    Report(int id, QString file);
    ~Report();
    void init(int id, QString file);

	int getId() const;
    void setId(int id);

    QString getFile() const;

	void removeFiles();

    virtual ReportType getType() const =0;

    ReportDataJson* getDataJson() const;
    void setDataJson(ReportDataJson* data);

    virtual QString getTemplateFile() const =0;

	bool operator==(const Report& report) const;
};
