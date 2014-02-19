#include "SessionBuilder.h"

/**
 * @brief Constructor
 * @param databaseFile The location of the database file on the disk.
 */
SessionBuilder::SessionBuilder(QString databaseFile): SQLiteManager(databaseFile) {

}

/**
 * @brief Retrieves an asset from the database.
 * @param name The name of the asset to retrieve.
 * @return The asset.
 */
Asset SessionBuilder::buildAsset(QString name) {
	// TODO
	return Asset(name, "", 0, 0);
}

/**
 * @brief Retrieves all assets from the database.
 * @return The assets.
 */
QVector<Asset> SessionBuilder::buildAssets() {
	// TODO
    return QVector<Asset>();
}

/**
 * @brief Retrieves a session from the database.
 * @return The portfolios of the session.
 */
QVector<Portfolio> SessionBuilder::buildSession() {
	// TODO
    return QVector<Portfolio>();
}

/**
 * @brief Retrieves all reports from the database.
 * @return The reports.
 */
QVector<Report> SessionBuilder::buildReports() {
	// TODO
    return QVector<Report>();
}

/**
 * @brief Retrieves all portfolios from the database.
 * @return The portfolios.
 */
QVector<Portfolio> SessionBuilder::buildPortfolios() {
	// TODO
    return QVector<Portfolio>();
}
