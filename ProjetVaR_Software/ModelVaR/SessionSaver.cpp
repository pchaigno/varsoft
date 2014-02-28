#include "SessionSaver.h"

SessionSaver* SessionSaver::instance;

/**
 * @brief Constructor
 * @param databaseFile The location of the database file on the disk.
 */
SessionSaver::SessionSaver(QString databaseFile): SQLiteManager(databaseFile) {

}

/**
 * @brief Save an asset in the database.
 * @param asset The asset to save.
 * @return True if the asset was successfully saved.
 */
bool SessionSaver::saveAsset(Asset& asset) {
	this->openConnection();
	QSqlQuery query;
	query.prepare("INSERT INTO assets(name, file, origin, first_date, last_date) VALUES(:name, :file, :origin, :first_date, :last_date);");
	query.bindValue(":name", asset.getFile());
	query.bindValue(":file", asset.getName());
	query.bindValue(":origin", asset.getOrigin());
	query.bindValue(":first_date", asset.getFirstDate());
	query.bindValue(":last_date", asset.getLastDate());
	bool result = query.exec();
	this->closeConnection();
	return result;
}

/**
 * @brief Save an entire session in the database.
 * @param portfolios The portfolios of the session.
 */
void SessionSaver::saveSession(const QVector<Portfolio>& portfolios) {
	// TODO
	this->savePortfolios(portfolios);
}

/**
 * @brief Save some assets in the database.
 * @param assets The assets to save.
 */
void SessionSaver::saveAssets(const QVector<Asset>& assets) {
	this->openConnection();
	QSqlQuery query;
	query.prepare("INSERT INTO assets(name, file, origin, first_date, last_date) VALUES(:name, :file, :origin, :first_date, :last_date);");
	for(QVector<Asset>::const_iterator asset=assets.begin(); asset!=assets.end(); ++asset) {
		query.bindValue(":name", asset->getFile());
		query.bindValue(":file", asset->getName());
		query.bindValue(":origin", asset->getOrigin());
		query.bindValue(":first_date", asset->getFirstDate());
		query.bindValue(":last_date", asset->getLastDate());
		query.execBatch();
	}
	this->closeConnection();
}

/**
 * @brief Save some portfolios in the database.
 * @param portfolios The portfolios to save.
 */
void SessionSaver::savePortfolios(const QVector<Portfolio>& portfolios) {
	this->openConnection();
	QSqlQuery query;
	query.prepare("INSERT INTO portfolios(name, parent) VALUES(:name, :parent);");
	for(QVector<Portfolio>::const_iterator portfolio=portfolios.begin(); portfolio!=portfolios.end(); ++portfolio) {
		query.bindValue(":name", portfolio->getName());
		query.bindValue(":parent", portfolio->getParentId());
		query.execBatch();
	}
	this->closeConnection();
}

/**
 * @brief Save some reports in the database.
 * @param portfolio The porfolios owner of the reports.
 * @param reports The reports to save.
 */
void SessionSaver::saveReports(const Portfolio& portfolio, const QVector<Report>& reports) {
	this->openConnection();
	QSqlQuery query;
	query.prepare("INSERT INTO reports(portfolio, pdf_file, docx_file, type) VALUES(:portfolio, :pdf_file, :docx_file, :type);");
	for(QVector<Report>::const_iterator report=reports.begin(); report!=reports.end(); ++report) {
		query.bindValue(":portfolio", portfolio.getId());
		query.bindValue(":pdf_file", report->getPDFFile());
		query.bindValue(":docx_file", report->getDOCXFile());
		query.bindValue(":type", report->getType());
		query.execBatch();
	}
	this->closeConnection();
}