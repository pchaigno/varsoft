#pragma once

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>

class SQLiteManager {
protected:
    const QString databaseFile;
	QSqlDatabase db;

protected:
	SQLiteManager(const QString databaseFile);
	bool openConnection();
	void closeConnection();
	bool createDatabase();
};