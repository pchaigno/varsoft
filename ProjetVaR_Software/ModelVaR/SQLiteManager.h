#pragma once

#include <string>

using namespace std;

class SQLiteManager {
protected:
	const string databaseFile;

protected:
	SQLiteManager(const string databaseFile);

private:
	// TODO Change returned object.
	void openConnection();
	void createDatabase();
};