#pragma once

#include <QString>

class SQLiteManager {
protected:
	const QString databaseFile;

protected:
	SQLiteManager(const QString databaseFile);
	void openConnection();

private:
	bool createDatabase();
	bool createTable(QString sqlQuery);
};