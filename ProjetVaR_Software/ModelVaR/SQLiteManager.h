#pragma once

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFile>
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT SQLiteManager {
protected:
    const QString databaseFile;
	QSqlDatabase db;

protected:
    SQLiteManager(const QString databaseFile);
	bool openConnection();
	void closeConnection();
	bool createDatabase();

public:
    QString getDatabaseFile() const;
};