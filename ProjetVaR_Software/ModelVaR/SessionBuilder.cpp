#include "SessionBuilder.h"

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
	QSqlQuery query;
	query.prepare("SELECT id, file, first_date, last_date FROM assets WHERE name = :name;");
	query.bindValue(":name", name);
	query.exec();

	int id;
	QString file, origin;
	QDateTime firstDate, lastDate;
	Asset* asset = NULL;
	if(query.next()) {
		id = query.value(0).toInt();
		file = query.value(1).toString();
		origin = query.value(2).toString();
		firstDate.setTime_t(query.value(3).toInt());
		lastDate.setTime_t(query.value(4).toInt());
		asset = new Asset(id, name, file, origin, firstDate, lastDate);
	}

	this->closeConnection();
	return asset;
}

/**
 * @brief Retrieves all assets from the database.
 * @return The assets.
 */
QVector<Asset> SessionBuilder::buildAssets() {
	this->openConnection();
	QSqlQuery query;
	query.exec("SELECT id, name, file, first_date, last_date FROM assets;");

	QVector<Asset> assets;
	int id;
	QString file, origin, name;
	QDateTime firstDate, lastDate;
	while(query.next()) {
		id = query.value(0).toInt();
		name = query.value(1).toString();
		file = query.value(2).toString();
		origin = query.value(3).toString();
		firstDate.setTime_t(query.value(4).toInt());
		lastDate.setTime_t(query.value(5).toInt());
		assets.append(Asset(id, name, file, origin, firstDate, lastDate));
	}

	this->closeConnection();
	return assets;
}

/**
 * @brief Retrieves a session from the database.
 * @return The portfolios of the session.
 */
QVector<Portfolio> SessionBuilder::buildSession() {
	AssetsFactory::getInstance();
	QVector<Portfolio> portfolios = this->buildPortfolios();
	return portfolios;
}

/**
 * @brief Retrieves all reports of a portfolio from the database.
 * @param idPortfolio The id of the portfolio.
 * @return The reports.
 */
QVector<Report> SessionBuilder::buildReports(int idPortfolio) {
	this->openConnection();
	QSqlQuery query;
	query.exec("SELECT id, docx_file, pdf_file FROM reports WHERE portfolio = :id_portfolio;");
	query.bindValue(":id_portfolio", idPortfolio);

	int id;
	QString docxFile, pdfFile;
	QVector<Report> reports;
	while(query.next()) {
		id = query.value(0).toInt();
		docxFile = query.value(1).toString();
		pdfFile = query.value(2).toString();
		reports.append(Report(id, docxFile, pdfFile));
	}

	this->closeConnection();
	return reports;
}

/**
 * @brief Retrieves all portfolios from the database.
 * @return The portfolios.
 */
QVector<Portfolio> SessionBuilder::buildPortfolios() {
	// TODO Should we have a mechanism to prevent the portfolios to be loop-linked?
	this->openConnection();
	QSqlQuery query;
	query.exec("SELECT id, name, parent FROM portfolios ORDER BY parent ASC;");

	QVector<Portfolio> portfolios;
	QMap<int, Portfolio*> portfoliosById;
	QVector<Report> reports;
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
		Portfolio portfolio = Portfolio(parent_ptr, id, name, assets, reports);
		portfolios.append(portfolio);
		portfoliosById[id] = &portfolio;
	}

	this->closeConnection();
	return portfolios;
}

/**
* @brief Retrieves the composition of a portfolio from the database (for the weights)
* and from the AssetsFactory (for the assets).
* @return The portfolio composition as a map.
*/
QMap<Asset*, int> SessionBuilder::buildPortfolioComposition(int idPortfolio) {
	this->openConnection();
	QSqlQuery query;
	query.exec("SELECT name, weight FROM weights, assets WHERE portfolio = :id_portfolio;");
	query.bindValue(":id_portfolio", idPortfolio);

	Asset* asset;
	QString assetName;
	int weight;
	QMap<Asset*, int> composition;
	while(query.next()) {
		assetName = query.value(0).toString();
		weight = query.value(1).toInt();
		asset = AssetsFactory::getInstance().retrieveAsset(assetName);
		composition[asset] = weight;
	}

	this->closeConnection();
	return composition;
}