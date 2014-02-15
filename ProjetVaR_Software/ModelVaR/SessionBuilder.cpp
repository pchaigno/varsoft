#include "SessionBuilder.h"

/**
 * @brief Retrieves an asset from the database.
 * @param name The name of the asset to retrieve.
 * @return The asset.
 */
Asset SessionBuilder::buildAsset(string name) {
	// TODO
	return Asset(name, "", 0, 0);
}

/**
 * @brief Retrieves all assets from the database.
 * @return The assets.
 */
vector<Asset> SessionBuilder::buildAssets() {
	// TODO
	return vector<Asset>();
}

/**
 * @brief Retrieves a session from the database.
 * @return The portfolios of the session.
 */
vector<Portfolio> SessionBuilder::buildSession() {
	// TODO
	return vector<Portfolio>();
}

/**
 * @brief Retrieves all reports from the database.
 * @return The reports.
 */
vector<Report> SessionBuilder::buildReports() {
	// TODO
	return vector<Report>();
}

/**
 * @brief Retrieves all portfolios from the database.
 * @return The portfolios.
 */
vector<Portfolio> SessionBuilder::buildPortfolios() {
	// TODO
	return vector<Portfolio>();
}