#include "SQLiteManager.h"

/**
 * @brief Constructor.
 * @param databaseFile The location of the database file on the disk.
 */
SQLiteManager::SQLiteManager(const QString databaseFile): databaseFile(databaseFile) {

}

/**
 * @brief Open the connection to the database.
 * @return An SQLite handler.
 */
void SQLiteManager::openConnection() {
	/*sqlite3* db;
	if(sqlite3_open("session.db", &db)) {
		return NULL;
	}
	return db;*/
}

/**
 * @brief Creates the database.
 * @return True if the database was successfully created.
 */
bool SQLiteManager::createDatabase() {
	/*sqlite3* db = this->openConnection();
	bool result = true;
	string sqlAssets, sqlPortfolios, sqlReports, sqlWeights;
	sqlAssets = "CREATE TABLE assets("  \
		"id INT PRIMARY KEY NOT NULL," \
		"name TEXT UNIQUE NOT NULL," \
		"file TEXT UNIQUE NOT NULL," \
		"origin TEXT," \
		"first_date INTEGER," \
		"last_date INTEGER);";
	result &= createTable(db, sqlAssets);
	sqlPortfolios = "CREATE TABLE portfolios("  \
		"id INT PRIMARY KEY NOT NULL," \
		"name TEXT UNIQUE NOT NULL," \
		"parent INT REFERENCES portfolios(id));";
	result &= createTable(db, sqlPortfolios);
	sqlWeights = "CREATE TABLE weights("  \
		"asset INT NOT NULL REFERENCES assets(id)," \
		"portfolio INT NOT NULL REFERENCES portfolio(id)," \
		"weight INT NOT NULL," \
		"PRIMARY KEY(asset, portfolio);)";
	result &= createTable(db, sqlWeights);
	sqlReports = "CREATE TABLE reports("  \
		"id INT PRIMARY KEY NOT NULL," \
		"portfolio INT NOT NULL REFERENCES portfolios(id)," \
		"pdf_file TEXT UNIQUE NOT NULL," \
		"docx_file TEXT UNIQUE NOT NULL," \
		"type INT NOT NULL);";
	result &= this->createTable(db, sqlReports);
	sqlite3_close(db);
	return result;*/
	return false;
}

/**
 * @brief Creates a table with the SQL query given.
 * Don't open nor close the connection to the database.
 * @param db The database connection.
 * @param sqlQuery The SQL query to create the table.
 * @return True if the table was created successfully.
 */
bool createTable(QString sqlQuery) {
	/*char *zErrMsg = 0;
	int result = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &zErrMsg);
	return result == SQLITE_OK;*/
	return false;
}