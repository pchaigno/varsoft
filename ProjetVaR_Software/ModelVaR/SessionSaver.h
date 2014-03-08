#pragma once

#include "SQLiteManager.h"
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"
#include <QVector>
#include <QString>
#include <QVariant>

class MODELVARSHARED_EXPORT SessionSaver: public SQLiteManager {
private:
	static SessionSaver* instance;

public:
	bool saveAsset(Asset& asset);
	void saveSession(QVector<Portfolio>& portfolios);
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
	SessionSaver(QString databaseFile);
	void saveAssets(QVector<Asset*> &assets);
	void savePortfolios(QVector<Portfolio>& portfolios);
	void saveReports(const Portfolio& portfolio, const QVector<Report*>& reports);
};
