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
#include "SessionBuilder.h"

SessionBuilder* SessionBuilder::instance;

/**
* @brief Constructor
* @param databaseFile The location of the database file on the disk.
*/
SessionBuilder::SessionBuilder(QString databaseFile): SQLiteManager(databaseFile) {

}

/**
* @brief Retrieves an asset from the database.
* @param name The name of the asset to retrieve.
* @return The asset.
*/
Asset* SessionBuilder::buildAsset(QString name) {
	this->openConnection();
	QSqlQuery query(this->db);
	query.prepare("SELECT id, file, origin, first_date, last_date FROM assets WHERE name = :name;");
	query.bindValue(":name", name);
	query.exec();

	int id;
	QString file, origin;
	QDate startDate, endDate;
	Asset* asset = NULL;
	if(query.next()) {
		id = query.value(0).toInt();
		file = query.value(1).toString();
		origin = query.value(2).toString();
		startDate = QDate::fromString(query.value(3).toString(), "yyyyMMdd");
		endDate = QDate::fromString(query.value(4).toString(), "yyyyMMdd");
		asset = new Asset(id, name, file, origin, startDate, endDate);
	}

	query.finish();
	this->closeConnection();
	return asset;
}

/**
* @brief Retrieves all assets from the database.
* @return The assets.
*/
QMap<QString, Asset*> SessionBuilder::buildAssets() {
	this->openConnection();
	QSqlQuery query(this->db);
	query.exec("SELECT id, name, file, origin, first_date, last_date FROM assets;");

	QMap<QString, Asset*> assets;
	int id;
	QString file, origin, name;
	QDate startDate, endDate;
	while(query.next()) {
		id = query.value(0).toInt();
		name = query.value(1).toString();
		file = query.value(2).toString();
		origin = query.value(3).toString();
		startDate = QDate::fromString(query.value(4).toString(), "yyyyMMdd");
		endDate = QDate::fromString(query.value(5).toString(), "yyyyMMdd");
		assets[name] = new Asset(id, name, file, origin, startDate, endDate);
	}

	query.finish();
	this->closeConnection();
	return assets;
}

/**
* @brief Retrieves a session from the database.
* @return The portfolios of the session.
*/

QList<Portfolio*> SessionBuilder::buildSession() {
	AssetsFactory::getInstance();
	this->openConnection();
	QList<Portfolio*> portfolios = this->buildPortfolios();
	this->closeConnection();
	return portfolios;
}

/**
* @brief Retrieves all portfolios from the database.
* @return The portfolios.
*/
QList<Portfolio*> SessionBuilder::buildPortfolios() {

	// TODO Should we have a mechanism to prevent the portfolios to be loop-linked?
	QSqlQuery query(this->db);
	query.exec("SELECT id, name, parent FROM portfolios ORDER BY parent ASC;");

	QList<Portfolio*> portfolios;
	QMap<int, Portfolio*> portfoliosById;
	QList<Report*> reports;
	QMap<Asset*, int> assets;
	QString name;
	int id, parent;
	Portfolio* parent_ptr;
	while(query.next()) {
		id = query.value(0).toInt();
		name = query.value(1).toString();
		reports = this->buildReports(id);
		assets = this->buildPortfolioComposition(id);
		parent = query.value(2).toInt();
		if(parent == 0) {
			parent_ptr = NULL;
		} else {
			parent_ptr = portfoliosById[parent];
		}
		Portfolio* portfolio = new Portfolio(parent_ptr, id, name, assets, reports);
		portfolios.append(portfolio);
		portfoliosById[id] = portfolio;
	}

	query.finish();
	return portfolios;
}

/**
* @brief Retrieves the composition of a portfolio from the database (for the weights)
* and from the AssetsFactory (for the assets).
* @return The portfolio composition as a map.
*/
QMap<Asset*, int> SessionBuilder::buildPortfolioComposition(int idPortfolio) {
	QSqlQuery query(this->db);
	query.prepare("SELECT name, weight FROM weights, assets WHERE asset = id AND portfolio = :id_portfolio;");
	query.bindValue(":id_portfolio", idPortfolio);
	query.exec();

	Asset* asset;
	QString assetName;
	int weight;
	QMap<Asset*, int> composition;
	while(query.next()) {
		assetName = query.value(0).toString();
		weight = query.value(1).toInt();
		asset = AssetsFactory::getInstance()->retrieveAsset(assetName);
		composition[asset] = weight;
	}

	query.finish();
	return composition;
}

/**
* @brief Retrieves all reports of a portfolio from the database.
* @param idPortfolio The id of the portfolio.
* @return The reports.
*/
QList<Report *> SessionBuilder::buildReports(int idPortfolio) {
	QSqlQuery query(this->db);
	query.prepare("SELECT id, file, type FROM reports WHERE portfolio = :id_portfolio;");
	query.bindValue(":id_portfolio", idPortfolio);
	query.exec();

	int id;
	ReportType type;
	QString file;
	QList<Report*> reports;
	while(query.next()) {
		id = query.value(0).toInt();
		file = query.value(1).toString();
		type = (ReportType)query.value(2).toInt();
		Report* report;
		switch(type) {
			case GARCH:
				report = new GarchReport(id, file);
				break;
			case VAR:
				report = new VaRReport(id, file);
				break;
			case STATISTICS:
				report = new StatisticsReport(id, file);
				break;
			case CORRELATION:
				report = new CorrelationReport(id, file);
				break;
			case BACKTESTING:
				report = new BacktestingReport(id, file);
				break;
			default:
				// TODO Throw exception? - oui
				break;
		}
		reports.append(report);
	}

	query.finish();
	return reports;
}
