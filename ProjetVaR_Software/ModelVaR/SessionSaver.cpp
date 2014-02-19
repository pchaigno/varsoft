#include "SessionSaver.h"

/**
 * @brief Constructor
 * @param databaseFile The location of the database file on the disk.
 */
SessionSaver::SessionSaver(string databaseFile): SQLiteManager(databaseFile) {

}

/**
 * @brief Save an asset in the database.
 * @param asset The asset to save.
 * @return True if the asset was successfully saved.
 */
bool SessionSaver::saveAsset(Asset& asset) {
	sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "INSERT INTO assets(name, file, origin, first_date, last_date) VALUES(?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	sqlite3_bind_text(preparedStmt, 0, asset.getName().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(preparedStmt, 1, asset.getFile().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(preparedStmt, 2, asset.getOrigin().c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_int(preparedStmt, 3, asset.getFirstDate());
	sqlite3_bind_int(preparedStmt, 4, asset.getLastDate());
	int result = sqlite3_step(preparedStmt);
	asset.setId(sqlite3_last_insert_rowid(db));
	return result == SQLITE_OK;
}

/**
 * @brief Save an entire session in the database.
 * @param portfolios The portfolios of the session.
 */
void SessionSaver::saveSession(const vector<Portfolio>& portfolios) {
	// TODO
	this->savePortfolios(portfolios);
}

/**
 * @brief Save some assets in the database.
 * @param assets The assets to save.
 */
void SessionSaver::saveAssets(const vector<Asset>& assets) {
	sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "INSERT INTO assets(name, file, origin, first_date, last_date) VALUES(?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	for(vector<Asset>::const_iterator it=assets.begin(); it!=assets.end(); ++it) {
		Asset asset = *it;
		sqlite3_bind_text(preparedStmt, 0, asset.getName().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(preparedStmt, 1, asset.getFile().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(preparedStmt, 2, asset.getOrigin().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(preparedStmt, 3, asset.getFirstDate());
		sqlite3_bind_int(preparedStmt, 4, asset.getLastDate());
		sqlite3_step(preparedStmt);
		asset.setId(sqlite3_last_insert_rowid(db));
		sqlite3_reset(preparedStmt);
	}
}

/**
 * @brief Save some portfolios in the database.
 * @param portfolios The portfolios to save.
 */
void SessionSaver::savePortfolios(const vector<Portfolio>& portfolios) {
	sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "INSERT INTO portfolios(name, parent) VALUES(?, ?);";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	for(vector<Portfolio>::const_iterator it=portfolios.begin(); it!=portfolios.end(); ++it) {
		Portfolio portfolio = *it;
		sqlite3_bind_text(preparedStmt, 0, portfolio.getName().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(preparedStmt, 1, portfolio.getParentId());
		sqlite3_step(preparedStmt);
		portfolio.setId(sqlite3_last_insert_rowid(db));
		sqlite3_reset(preparedStmt);
	}
}

/**
 * @brief Save some reports in the database.
 * @param portfolio The porfolios owner of the reports.
 * @param reports The reports to save.
 */
void SessionSaver::saveReports(const Portfolio& portfolio, const vector<Report>& reports) {
	sqlite3_stmt* preparedStmt;
	sqlite3* db = this->openConnection();
	string sqlQuery = "INSERT INTO reports(portfolio, pdf_file, docx_file, type) VALUES(?, ?, ?, ?);";
	sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &preparedStmt, NULL);
	for(vector<Report>::const_iterator it=reports.begin(); it!=reports.end(); ++it) {
		Report report = *it;
		sqlite3_bind_int(preparedStmt, 0, portfolio.getId());
		sqlite3_bind_text(preparedStmt, 1, report.getPDFFile().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(preparedStmt, 2, report.getDOCXFile().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(preparedStmt, 3, report.getType());
		sqlite3_step(preparedStmt);
		report.setId(sqlite3_last_insert_rowid(db));
		sqlite3_reset(preparedStmt);
	}
}