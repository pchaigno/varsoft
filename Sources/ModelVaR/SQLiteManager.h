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
#pragma once

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>
#include "ModelVaR_global.h"
#include "SessionFolderMissingException.h"

class MODELVARSHARED_EXPORT SQLiteManager {
private:
	static QString sessionFolder;

protected:
	const QString databaseFile;
	QSqlDatabase db;

protected:
	SQLiteManager(const QString databaseFile);
	bool openConnection();
	void closeConnection();
	bool createDatabase();

	/**
	 * @brief Builds the database file path from the session folder path.
	 * @return The database file path.
	 */
	static QString buildDatabaseFilePath() {
		if(sessionFolder == "") {
			throw SessionFolderMissingException("No session folder has been defined.");
		}
		return sessionFolder + QDir::separator() + "session.db";
	}

public:
	QString getDatabaseFile() const;

	/**
	 * @brief Sets the session folder.
	 * @param folder The folder where the session will be saved.
	 */
	static void setSessionFolder(QDir folder) {
		sessionFolder = folder.absolutePath();
	}

	/**
	 * @return The session folder.
	 */
	static QString getSessionFolder() {
		return sessionFolder;
	}
};
