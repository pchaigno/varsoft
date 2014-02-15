#pragma once

#include "SQLiteManager.h"
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <vector>

class SessionSaver: public SQLiteManager {
public:
	static void saveAsset(const Asset& asset);
	static void saveSession(const vector<Portfolio>& portfolios);

private:
	static void saveAssets(const vector<Asset>& assets);
	static void savePortfolios(const vector<Portfolio>& portfolios);
	static void saveReports(const Portfolio& portfolio, const vector<Report>& reports);
};