#include "SQLiteManager.h"

/**
 * @brief Constructor.
 * @param databaseFile The location of the database file on the disk.
 */
SQLiteManager::SQLiteManager(const string databaseFile): databaseFile(databaseFile) {

}

/**
 * @brief Open the connection to the database.
 * @return An SQLite handler.
 */
void SQLiteManager::openConnection() {
	sqlite3* db;
	int rc;
	rc = sqlite3_open("session.db", &db);
	if(rc) {
		fprintf(stderr, "Can't open database.\n");
	}
	sqlite3_close(db);
}

/**
 * @brief Creates the database.
 */
void SQLiteManager::createDatabase() {
	/*sql = "CREATE TABLE COMPANY("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"ADDRESS        CHAR(50)," \
		"SALARY         REAL );";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(rc == SQLITE_OK) {
		fprintf(stdout, "Table created successfully\n");
	} else {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);*/
}