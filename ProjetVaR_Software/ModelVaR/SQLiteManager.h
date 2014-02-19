#pragma once

#include <string>
#include "sqlite3.h"

using namespace std;

class SQLiteManager {
protected:
	const string databaseFile;

public:
	// TODO Any way to do it cleaner?
	static string chars_to_string(const unsigned char* chars);

protected:
	SQLiteManager(const string databaseFile);
	sqlite3* openConnection();

private:
	bool createDatabase();
	bool createTable(sqlite3* db, string sqlQuery);
};