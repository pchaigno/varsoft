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
#include "SQLiteManager.h"

/**
 * @brief Constructor.
 * @param databaseFile The location of the database file on the disk.
 */
SQLiteManager::SQLiteManager(const QString databaseFile): databaseFile(databaseFile) {

}

/**
 * @brief Accessor to database file.
 * @return The location of the database file.
 */
QString SQLiteManager::getDatabaseFile() const {
	return this->databaseFile;
}

/**
 * @brief Open the connection to the database.
 * @return An SQLite handler.
 */
bool SQLiteManager::openConnection() {
	// Checks if the database already existed:
	QFile file(this->databaseFile);
	bool databaseCreated = file.exists();
	this->db = QSqlDatabase::addDatabase("QSQLITE");
	this->db.setDatabaseName(this->databaseFile);
	bool result = this->db.open();
	if(!result) {
		return result;
	}
	// Creates the tables if they don't exist:
	if(!databaseCreated) {
		this->createDatabase();
	}
	return result;
}

/**
 * @brief Close the connection to the database.
 */
void SQLiteManager::closeConnection() {
	QString connectionName = this->db.connectionName();
	this->db.close();
	QSqlDatabase::removeDatabase(connectionName);
}

/**
 * @brief Creates the database.
 * @return True if the database was created successfully.
 */
bool SQLiteManager::createDatabase() {
	QString sqlAssets, sqlPortfolios, sqlReports, sqlWeights;
	bool result = true;
	QSqlQuery query;
	sqlAssets = "CREATE TABLE assets("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT UNIQUE NOT NULL,"
		"file TEXT UNIQUE NOT NULL,"
		"origin TEXT,"
		"first_date INTEGER,"
		"last_date INTEGER);";
	result &= query.exec(sqlAssets);
	sqlPortfolios = "CREATE TABLE portfolios("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT UNIQUE NOT NULL,"
		"parent INTEGER);";
	result &= query.exec(sqlPortfolios);
	sqlWeights = "CREATE TABLE weights("
		"asset INTEGER NOT NULL REFERENCES assets(id),"
		"portfolio INTEGER NOT NULL REFERENCES portfolio(id),"
		"weight INTEGER NOT NULL,"
		"PRIMARY KEY(asset, portfolio));";
	result &= query.exec(sqlWeights);
	sqlReports = "CREATE TABLE reports("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"portfolio INTEGER NOT NULL REFERENCES portfolios(id),"
		"pdf_file TEXT UNIQUE NOT NULL,"
		"docx_file TEXT UNIQUE NOT NULL,"
		"type INTEGER NOT NULL);";
	result &= query.exec(sqlReports);
	query.finish();
	return result;
}
