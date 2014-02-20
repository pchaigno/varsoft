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
bool SQLiteManager::openConnection() {
	this->db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(this->databaseFile);
	return db.open();
}

/**
 * @brief Close the connection to the database.
 */
void SQLiteManager::closeConnection() {
	this->db.close();
}

/**
 * @brief Creates the database.
 * @return True if the database was created successfully.
 */
bool SQLiteManager::createDatabase() {
	this->openConnection();
	QString sqlAssets, sqlPortfolios, sqlReports, sqlWeights;
	bool result = true;
	QSqlQuery query;
	sqlAssets = "CREATE TABLE assets("
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT UNIQUE NOT NULL,"
		"file TEXT UNIQUE NOT NULL,"
		"origin TEXT,"
		"first_date INTEGER,"
		"last_date INTEGER);";
	result &= query.exec(sqlAssets);
	sqlPortfolios = "CREATE TABLE portfolios("
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT UNIQUE NOT NULL,"
		"parent INT REFERENCES portfolios(id));";
	result &= query.exec(sqlPortfolios);
	sqlWeights = "CREATE TABLE weights("
		"asset INT NOT NULL REFERENCES assets(id),"
		"portfolio INT NOT NULL REFERENCES portfolio(id),"
		"weight INT NOT NULL,"
		"PRIMARY KEY(asset, portfolio);)";
	result &= query.exec(sqlWeights);
	sqlReports = "CREATE TABLE reports("
		"id INT PRIMARY KEY NOT NULL,"
		"portfolio INT NOT NULL REFERENCES portfolios(id),"
		"pdf_file TEXT UNIQUE NOT NULL,"
		"docx_file TEXT UNIQUE NOT NULL,"
		"type INT NOT NULL);";
	result &= query.exec(sqlReports);
	return result;
}