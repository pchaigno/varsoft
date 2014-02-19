#include "SessionSaver.h"

/**
 * @brief Constructor
 * @param databaseFile The location of the database file on the disk.
 */
SessionSaver::SessionSaver(QString databaseFile): SQLiteManager(databaseFile) {

}

/**
 * @brief Save an asset in the database.
 * @param asset The asset to save.
 */
void SessionSaver::saveAsset(const Asset& asset) {
	// TODO
}

/**
 * @brief Save an entire session in the database.
 * @param portfolios The portfolios of the session.
 */
void SessionSaver::saveSession(const QVector<Portfolio> &portfolios) {
	// TODO
}

/**
 * @brief Save some assets in the database.
 * @param assets The assets to save.
 */
void SessionSaver::saveAssets(const QVector<Asset> &assets) {
	// TODO
}

/**
 * @brief Save some portfolios in the database.
 * @param portfolios The portfolios to save.
 */
void SessionSaver::savePortfolios(const QVector<Portfolio>& portfolios) {
	// TODO
}

/**
 * @brief Save some reports in the database.
 * @param portfolio The porfolios owner of the reports.
 * @param reports The reports to save.
 */
void SessionSaver::saveReports(const Portfolio& portfolio, const QVector<Report> &reports) {
	// TODO
}
