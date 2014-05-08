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

#include "SQLiteManager.h"
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <QVector>
#include <QList>
#include <QString>
#include <QVariant>

class MODELVARSHARED_EXPORT SessionSaver: public SQLiteManager {
private:
	static SessionSaver* instance;

public:
	bool saveAsset(Asset& asset);
	void saveSession(QList<Portfolio*> portfolios);
	/**
	 * @brief Accessor to the only instance of SessionSaver.
	 * @return The only instance of SessionSaver.
	 */
	static SessionSaver* getInstance() {
		if(instance == NULL) {
			instance = new SessionSaver("session.db");
		}
		return instance;
	}

private:
	SessionSaver(QString databaseFile);
	void saveAssets(QVector<Asset*> &assets);
	void savePortfolios(QList<Portfolio*> portfolios);
	void saveReports(const Portfolio* portfolio, const QList<Report*>& reports);
};
