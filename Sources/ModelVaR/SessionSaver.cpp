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
#include "SessionSaver.h"

SessionSaver* SessionSaver::instance;

/**
 * @brief Constructor
 * @param databaseFile The location of the database file on the disk.
 */
SessionSaver::SessionSaver(QString databaseFile): SQLiteManager(databaseFile) {

}

/**
 * @brief Save an asset in the database.
 * Will return false if the asset is already in the database.
 * @param asset The asset to save.
 * @return True if the asset was successfully saved.
 */
bool SessionSaver::saveAsset(Asset& asset) {
	if(!asset.isAbsent()) {
		return false;
	}
	this->openConnection();
	QSqlQuery query(this->db);
	query.prepare("INSERT INTO assets(id, name, file, origin, first_date, last_date) VALUES(NULL, :name, :file, :origin, :first_date, :last_date);");
	query.bindValue(":name", asset.getName());
	query.bindValue(":file", asset.getFile());
	query.bindValue(":origin", asset.getOrigin());
	query.bindValue(":first_date", asset.getStartDate().toString("yyyyMMdd"));
	query.bindValue(":last_date", asset.getEndDate().toString("yyyyMMdd"));
	bool result = query.exec();
	asset.setId(query.lastInsertId().toInt());

	query.finish();
	this->closeConnection();
	return result;
}

/**
 * @brief Saves an entire session in the database.
 * @param portfolios The portfolios of the session.
 */
void SessionSaver::saveSession(QList<Portfolio*> portfolios) {
	this->openConnection();

	// The assets must be saved first:
	QList<Asset*> allAssets;
	foreach(Portfolio* portfolio, portfolios) {
		allAssets.append(portfolio->getAssets());
	}
	this->saveAssets(allAssets);
	this->updateAssets(allAssets);

	// Now it's possible to save the portfolios:
	this->savePortfolios(portfolios);
	this->updatePortfolios(portfolios);

	// Searches for deleted portfolios:
	QList<int> deletedPortfolios;
	QList<int> portfoliosID = this->getPortfolios();
	foreach(int portfolioID, portfoliosID) {
		bool found = false;
		foreach(Portfolio* portfolio, portfolios) {
			if(portfolioID == portfolio->getId()) {
				found = true;
			}
		}
		if(!found) {
		// This portfolio has been deleted.
			deletedPortfolios.append(portfolioID);
		}
	}

	// The reports are saved last because they have a reference to a portfolio:
	foreach(Portfolio* portfolio, portfolios) {
		this->saveReports(portfolio, portfolio->getReports());
	}

	this->closeConnection();
}

/**
 * @brief Saves some assets in the database.
 * The assets already in the database will be ignored.
 * @param assets The assets to save.
 */
void SessionSaver::saveAssets(QList<Asset*>& assets) const {
	QSqlQuery query(this->db);
	query.prepare("INSERT INTO assets(id, name, file, origin, first_date, last_date) VALUES(NULL, :name, :file, :origin, :first_date, :last_date);");
	foreach(Asset* asset, assets) {
		if(asset->isAbsent()) {
			query.bindValue(":name", asset->getName());
			query.bindValue(":file", asset->getFile());
			query.bindValue(":origin", asset->getOrigin());
			query.bindValue(":first_date", asset->getStartDate().toString("yyyyMMdd"));
			query.bindValue(":last_date", asset->getEndDate().toString("yyyyMMdd"));
			query.exec();
			asset->setId(query.lastInsertId().toInt());
		}
	}
	query.finish();
}

/**
 * @brief Updates the assets in the database.
 * The assets which haven't been modified will be ignored.
 * @param assets The assets to update.
 */
void SessionSaver::updateAssets(QList<Asset*>& assets) const {
	QSqlQuery query(this->db);
	query.prepare("UPDATE assets SET name = :name WHERE id = :id;");
	foreach(Asset* asset, assets) {
		if(asset->isModified()) {
			query.bindValue(":name", asset->getName());
			query.bindValue(":id", asset->getId());
			query.exec();
			asset->setStatusToUpToDate();
		}
	}
	query.finish();
}

/**
 * @brief Saves some portfolios in the database.
 * The portfolios already in the database will be ignored.
 * @param portfolios The portfolios to save.
 */
void SessionSaver::savePortfolios(QList<Portfolio*> portfolios) const {
	QSqlQuery queryPortfolios(this->db);
	QSqlQuery queryWeights(this->db);
	queryPortfolios.prepare("INSERT INTO portfolios(id, name, parent) VALUES(NULL, :name, :parent);");
	queryWeights.prepare("INSERT INTO weights(asset, portfolio, weight) VALUES(:asset, :portfolio, :weight);");
	foreach(Portfolio* portfolio, portfolios) {
		if(portfolio->isAbsent()) {
			queryPortfolios.bindValue(":name", portfolio->getName());
			queryPortfolios.bindValue(":parent", portfolio->getParentId());
			queryPortfolios.exec();
			portfolio->setId(queryPortfolios.lastInsertId().toInt());
			QMap<Asset*, int> composition = portfolio->getComposition();
			for(QMap<Asset*, int>::iterator it=composition.begin(); it!=composition.end(); ++it) {
				queryWeights.bindValue(":asset", it.key()->getId());
				queryWeights.bindValue(":portfolio", portfolio->getId());
				queryWeights.bindValue(":weight", it.value());
				queryWeights.exec();
			}
		}
	}
	queryWeights.finish();
	queryPortfolios.finish();
}

/**
 * @brief Updates the portfolios in the database.
 * The portfolios which haven't been modified will be ignored.
 * @param portfolios The portfolios to update.
 */
void SessionSaver::updatePortfolios(QList<Portfolio*> portfolios) const {
	QSqlQuery queryPortfolios(this->db);
	queryPortfolios.prepare("UPDATE portfolios SET name = :name WHERE id = :id;");
	QList<int> deletedReports;
	foreach(Portfolio* portfolio, portfolios) {
		if(portfolio->isModified()) {
			queryPortfolios.bindValue(":name", portfolio->getName());
			queryPortfolios.bindValue(":id", portfolio->getId());
			queryPortfolios.exec();

			// Searches for deleted reports:
			QList<int> reportsID = this->getReports(portfolio->getId());
			foreach(int reportID, reportsID) {
				bool reportFound = false;
				foreach(Report* report, portfolio->getReports()) {
					if(report->getId() == reportID) {
						reportFound = true;
					}
				}
				if(!reportFound) {
				// This report has been deleted as it isn't anymore in the portfolio.
					deletedReports.append(reportID);
				}
			}

			portfolio->setStatusToUpToDate();
		}
	}
	this->removeReports(deletedReports);

	queryPortfolios.finish();
}

/**
 * @brief Retrieves all portfolios' ID from the database.
 * @return All portfolios' ID.
 */
QList<int> SessionSaver::getPortfolios() const {
	QSqlQuery query(this->db);
	query.prepare("SELECT id FROM portfolios;");
	query.exec();

	QList<int> portfoliosID;
	while(query.next()) {
		portfoliosID.append(query.value(0).toInt());
	}

	query.finish();
	return portfoliosID;
}

/**
 * @brief Removes somes portfolios from the database.
 * Removes any references to the portfolios first in weights and reports.
 * @param portfoliosID The ID of the portfolios to remove from the database.
 */
void SessionSaver::removePortfolios(const QList<int> portfoliosID) const {
	QSqlQuery queryWeights(this->db);
	queryWeights.prepare("DELETE FROM weights WHERE portfolio = :id;");
	QSqlQuery queryReports(this->db);
	queryReports.prepare("DELETE FROM reports WHERE portfolio = :id;");
	QSqlQuery queryPortfolios(this->db);
	queryPortfolios.prepare("DELETE FROM portfolios WHERE id = :id;");
	foreach(int portfolioID, portfoliosID) {
		queryWeights.bindValue(":id", portfolioID);
		queryWeights.exec();
		queryReports.bindValue(":id", portfolioID);
		queryReports.exec();
		queryPortfolios.bindValue(":id", portfolioID);
		queryPortfolios.exec();
	}
	queryWeights.finish();
	queryReports.finish();
	queryPortfolios.finish();
}

/**
 * @brief Retrieves all reports' ID from the database.
 * @return All reports' ID.
 */
QList<int> SessionSaver::getReports(int portfolioID) const {
	QSqlQuery query(this->db);
	query.prepare("SELECT id FROM reports WHERE portfolio = :portfolio;");
	query.bindValue(":portfolio", portfolioID);
	query.exec();

	QList<int> reportsID;
	while(query.next()) {
		reportsID.append(query.value(0).toInt());
	}

	query.finish();
	return reportsID;
}

/**
 * @brief Removes some reports from the database.
 * @param reportsID The ID of the reports to remove from the database.
 */
void SessionSaver::removeReports(const QList<int> reportsID) const {
	QSqlQuery query(this->db);
	query.prepare("DELETE FROM reports WHERE id = :id;");
	foreach(int reportID, reportsID) {
		query.bindValue(":id", reportID);
		query.exec();
	}
	query.finish();
}

/**
 * @brief Saves some reports in the database.
 * The reports already in the database will be ignored.
 * @param portfolio The porfolios owner of the reports.
 * @param reports The reports to save.
 */
void SessionSaver::saveReports(const Portfolio* portfolio, const QList<Report*>& reports) const {
	QSqlQuery query(this->db);
	query.prepare("INSERT INTO reports(id, portfolio, file, type) VALUES(NULL, :portfolio, :file, :type);");
	foreach(Report* report, reports) {
		if(report->isAbsent()) {
			query.bindValue(":portfolio", portfolio->getId());
			query.bindValue(":file", report->getFile());
			query.bindValue(":type", report->getType());
			query.exec();
			report->setId(query.lastInsertId().toInt());
		}
	}
	query.finish();
}
