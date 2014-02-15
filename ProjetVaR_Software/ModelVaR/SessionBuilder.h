#pragma once

#include "SQLiteManager.h"
#include <string>
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <vector>

using namespace std;

class SessionBuilder: public SQLiteManager {
public:
	static Asset buildAsset(string name);
	static vector<Asset> buildAssets();
	static vector<Portfolio> buildSession();

private:
	static vector<Portfolio> buildPortfolios();
	static vector<Report> buildReports();
};