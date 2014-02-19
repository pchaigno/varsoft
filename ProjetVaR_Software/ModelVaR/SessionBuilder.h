#pragma once

#include "SQLiteManager.h"
#include <string>
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <vector>


class SessionBuilder: public SQLiteManager {
private:
	static SessionBuilder* instance;

public:
    Asset buildAsset(QString name);
    QVector<Asset> buildAssets();
    QVector<Portfolio> buildSession();
	/**
	 * @brief Accessor to the only instance of SessionBuilder.
	 * @return The only instance of SessionBuilder.
	 */
	static SessionBuilder* getInstance() {
		if(instance == NULL) {
			instance = new SessionBuilder("session.db");
		}
		return instance;
	}

private:
    SessionBuilder(QString databaseFile);
    QVector<Portfolio> buildPortfolios();
    QVector<Report> buildReports();
};
