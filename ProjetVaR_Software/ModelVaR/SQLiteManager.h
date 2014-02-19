#pragma once

#include <QString>

class SQLiteManager {
protected:
    const QString databaseFile;

protected:
    SQLiteManager(const QString databaseFile);

private:
	// TODO Change returned object.
	void openConnection();
	void createDatabase();
};