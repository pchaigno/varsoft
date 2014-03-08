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
	QSqlQuery query(this->db);
	query.prepare("INSERT INTO assets(id, name, file, origin, first_date, last_date) VALUES(NULL, :name, :file, :origin, :first_date, :last_date);");
	query.bindValue(":name", asset.getFile());
	query.bindValue(":file", asset.getName());
	query.bindValue(":origin", asset.getOrigin());
	query.bindValue(":first_date", asset.getFirstDate());
	query.bindValue(":last_date", asset.getLastDate());
	bool result = query.exec();
	asset.setId(query.lastInsertId().toInt());

	query.finish();
	this->closeConnection();
	return result;
}

/**
 * @brief Save an entire session in the database.
 * @param portfolios The portfolios of the session.
 */
void SessionSaver::saveSession(QVector<Portfolio>& portfolios) {
	this->openConnection();
	// The assets must be saved first:
	QVector<Asset*> allAssets;
	for(int i=0; i<portfolios.size(); i++) {
		QVector<Asset*> assets = portfolios[i].getAssets();
		for(int j=0; j<assets.size(); j++) {
			allAssets.append(assets[j]);
		}
	}
	this->saveAssets(allAssets);
	// Now it's possible to save the portfolios:
	this->savePortfolios(portfolios);
	// The reports are saved last because they have a reference to a portfolio:
	for(int i=0; i<portfolios.size(); i++) {
		this->saveReports(portfolios[i], portfolios[i].getReports());
	}
	this->closeConnection();
}

/**
 * @brief Save some assets in the database.
 * @param assets The assets to save.
 */
void SessionSaver::saveAssets(QVector<Asset*>& assets) {
	QSqlQuery query(this->db);
	query.prepare("INSERT INTO assets(id, name, file, origin, first_date, last_date) VALUES(NULL, :name, :file, :origin, :first_date, :last_date);");
	for(QVector<Asset*>::iterator it=assets.begin(); it!=assets.end(); ++it) {
		Asset* asset = *it;
		query.bindValue(":name", asset->getName());
		query.bindValue(":file", asset->getFile());
		query.bindValue(":origin", asset->getOrigin());
		query.bindValue(":first_date", asset->getFirstDate());
		query.bindValue(":last_date", asset->getLastDate());
		query.exec();
		asset->setId(query.lastInsertId().toInt());
	}
	query.finish();
}

/**
 * @brief Save some portfolios in the database.
 * @param portfolios The portfolios to save.
 */
void SessionSaver::savePortfolios(QVector<Portfolio>& portfolios) {
	QSqlQuery queryPortfolios(this->db);
	QSqlQuery queryWeights(this->db);
	queryPortfolios.prepare("INSERT INTO portfolios(id, name, parent) VALUES(NULL, :name, :parent);");
	queryWeights.prepare("INSERT INTO weights(asset, portfolio, weight) VALUES(:asset, :portfolio, :weight);");
	for(QVector<Portfolio>::iterator portfolio=portfolios.begin(); portfolio!=portfolios.end(); ++portfolio) {
		queryPortfolios.bindValue(":name", portfolio->getName());
		queryPortfolios.bindValue(":parent", portfolio->getParentId());
		queryPortfolios.exec();
		portfolio->setId(queryPortfolios.lastInsertId().toInt());
		QMap<Asset*, int> composition = portfolio->getComposition();
		for(QMap<Asset*, int>::iterator it=composition.begin(); it!=composition.end(); ++it) {
			queryWeights.bindValue(":asset", it.key()->getId());
			queryWeights.bindValue(":portfolio", portfolio->getId());
			queryWeights.bindValue(":weight", it.value());
			queryWeights.exec();
		}
	}
	queryWeights.finish();
	queryPortfolios.finish();
}

/**
 * @brief Save some reports in the database.
 * @param portfolio The porfolios owner of the reports.
 * @param reports The reports to save.
 */
void SessionSaver::saveReports(const Portfolio& portfolio, const QVector<Report*>& reports) {
	QSqlQuery query(this->db);
	query.prepare("INSERT INTO reports(id, portfolio, pdf_file, docx_file, type) VALUES(NULL, :portfolio, :pdf_file, :docx_file, :type);");
	for(int i=0; i<reports.size(); i++) {
		query.bindValue(":portfolio", portfolio.getId());
		query.bindValue(":pdf_file", reports[i]->getPDFFile());
		query.bindValue(":docx_file", reports[i]->getDOCXFile());
		query.bindValue(":type", reports[i]->getType());
		query.exec();
		reports[i]->setId(query.lastInsertId().toInt());
	}
	query.finish();
}
