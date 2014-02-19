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
	/*sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "SELECT id, file, first_date, last_date FROM assets WHERE name = ?;";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	sqlite3_bind_text(preparedStmt, 0, name.c_str(), -1, SQLITE_STATIC);
	int id;
	string file, origin;
	time_t firstDate, lastDate;
	Asset* asset = NULL;
	if(sqlite3_step(preparedStmt) == SQLITE_ROW) {
		id = sqlite3_column_int(preparedStmt, 0);
		file = chars_to_string(sqlite3_column_text(preparedStmt, 1));
		origin = chars_to_string(sqlite3_column_text(preparedStmt, 2));
		firstDate = sqlite3_column_int(preparedStmt, 3);
		lastDate = sqlite3_column_int(preparedStmt, 4);
		asset = new Asset(id, name, file, origin, firstDate, lastDate);
	}
	sqlite3_close(db);
	return asset;*/
	return NULL;
}

/**
 * @brief Retrieves all assets from the database.
 * @return The assets.
 */
QVector<Asset> SessionBuilder::buildAssets() {
	/*sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "SELECT id, name, file, origin, first_date, last_date FROM assets;";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	string name, file, origin;
	int id;
	time_t firstDate, lastDate;
	vector<Asset> assets = vector<Asset>();
	while(sqlite3_step(preparedStmt) == SQLITE_ROW) {
		id = sqlite3_column_int(preparedStmt, 0);
		name = chars_to_string(sqlite3_column_text(preparedStmt, 1));
		file = chars_to_string(sqlite3_column_text(preparedStmt, 2));
		origin = chars_to_string(sqlite3_column_text(preparedStmt, 3));
		firstDate = sqlite3_column_int(preparedStmt, 4);
		lastDate = sqlite3_column_int(preparedStmt, 5);
		assets.push_back(Asset(id, name, file, origin, firstDate, lastDate));
	}
	sqlite3_close(db);
	return assets;*/
	return QVector<Asset>();
}

/**
 * @brief Retrieves a session from the database.
 * @return The portfolios of the session.
 */
QVector<Portfolio> SessionBuilder::buildSession() {
	// Calls the AssetsFactory only to build the instance that will call buildAssets.
	/*AssetsFactory::getInstance();
	vector<Portfolio> portfolios = this->buildPortfolios();
	return portfolios;*/
	return QVector<Portfolio>();
}

/**
 * @brief Retrieves all reports of a portfolio from the database.
 * Don't open nor close the connection to the database.
 * @param db The connection handler to the database.
 * @param idPortfolio The ID of the portfolio.
 * @return The reports.
 */
QVector<Report> SessionBuilder::buildReports(int idPortfolio) {
	/*sqlite3_stmt* preparedStmt;
	string sqlQuery = "SELECT id, docx_file, pdf_file FROM reports WHERE portfolio = ?;";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	sqlite3_bind_int(preparedStmt, 0, idPortfolio);
	int id;
	string docxFile, pdfFile;
	vector<Report> reports = vector<Report>();
	while(sqlite3_step(preparedStmt) == SQLITE_ROW) {
		id = sqlite3_column_int(preparedStmt, 0);
		docxFile = chars_to_string(sqlite3_column_text(preparedStmt, 1));
		pdfFile = chars_to_string(sqlite3_column_text(preparedStmt, 2));
		reports.push_back(Report(id, docxFile, pdfFile));
	}
	return reports;*/
	return QVector<Report>();
}

/**
 * @brief Retrieves all portfolios from the database.
 * @return The portfolios.
 */
QVector<Portfolio> SessionBuilder::buildPortfolios() {
	// TODO Should we have a mechanism to prevent the portfolios to be loop-linked?
	/*sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "SELECT id, name, parent FROM portfolios ORDER BY parent ASC;";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	vector<Portfolio> portfolios = vector<Portfolio>();
	map<int, Portfolio*> portfoliosById = map<int, Portfolio*>();
	vector<Report> reports;
	map<Asset*, int> assets;
	string name;
	int id, parent;
	Portfolio* parent_ptr;
	while(sqlite3_step(preparedStmt) == SQLITE_ROW) {
		id = sqlite3_column_int(preparedStmt, 0);
		name = chars_to_string(sqlite3_column_text(preparedStmt, 1));
		reports = this->buildReports(db, id);
		assets = this->buildPortfolioComposition(db, id);
		parent = sqlite3_column_int(preparedStmt, 2);
		if(parent == 0) {
			parent_ptr = NULL;
		} else {
			parent_ptr = portfoliosById[parent];
		}
		Portfolio portfolio = Portfolio(parent_ptr, id, name, assets, reports);
		portfolios.push_back(portfolio);
		portfoliosById[id] = &portfolio;
	}
	sqlite3_close(db);
	return portfolios;*/
	return QVector<Portfolio>();
}

/**
 * @brief Retrieves the composition of a portfolio from the database (for the weights)
 * and from the AssetsFactory (for the assets).
 * @return The portfolio composition as a map.
 */
QMap<Asset*, int> SessionBuilder::buildPortfolioComposition(int idPortfolio) {
	/*sqlite3_stmt* preparedStmt;
	string sqlQuery = "SELECT name, weight FROM weights, assets WHERE portfolio = ?;";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	sqlite3_bind_int(preparedStmt, 0, idPortfolio);
	Asset* asset;
	string assetName;
	int weight;
	map<Asset*, int> composition = map<Asset*, int>();
	while(sqlite3_step(preparedStmt) == SQLITE_ROW) {
		assetName = chars_to_string(sqlite3_column_text(preparedStmt, 0));
		weight = sqlite3_column_int(preparedStmt, 1);
		asset = AssetsFactory::getInstance()->retrieveAsset(assetName);
		composition[asset] = weight;
	}
	return composition;*/
	return QMap<Asset*, int>();
}
