#pragma once

#include "SQLiteManager.h"
#include <string>
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <vector>
#include <map>
#include "AssetsFactory.h"
#include <ctime>

using namespace std;

class SessionBuilder: public SQLiteManager {
private:
	static SessionBuilder* instance;

public:
	Asset* buildAsset(string name);
	vector<Asset> buildAssets();
	vector<Portfolio> buildSession();
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
	SessionBuilder(string databaseFile);
	vector<Portfolio> buildPortfolios();
	vector<Report> buildReports(sqlite3* db, int idPortfolio);
	map<Asset*, int> buildPortfolioComposition(sqlite3* db, int idPortfolio);
};