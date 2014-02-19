#pragma once

#include "SQLiteManager.h"
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <string>
#include <vector>

using namespace std;

class SessionSaver: public SQLiteManager {
private:
	static SessionSaver* instance;

public:
	bool saveAsset(Asset &asset);
	void saveSession(const vector<Portfolio>& portfolios);
	/**
	 * @brief Accessor to the only instance of SessionSaver.
	 * @return The only instance of SessionSaver.
	 */
	static SessionSaver* getInstance() {
		if(instance == NULL) {
			instance = new SessionSaver("session.db");
		}
		return instance;
	}

private:
	SessionSaver(string databaseFile);
	void saveAssets(const vector<Asset>& assets);
	void savePortfolios(const vector<Portfolio> &portfolios);
	void saveReports(const Portfolio& portfolio, const vector<Report>& reports);
};