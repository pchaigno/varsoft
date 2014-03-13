#pragma once

#include "SQLiteManager.h"
#include <QString>
#include "Portfolio.h"
#include "Asset.h"
#include "GarchReport.h"
#include "VaRReport.h"
#include "StatisticsReport.h"
#include "CorrelationReport.h"
#include "BacktestingReport.h"
#include <QDateTime>
#include <QVector>
#include "AssetsFactory.h"
#include <QVariant>


class MODELVARSHARED_EXPORT SessionBuilder: public SQLiteManager {
private:
	static SessionBuilder* instance;

public:
	Asset *buildAsset(QString name);
	QMap<QString, Asset*> buildAssets();
	QVector<Portfolio> buildSession();
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
	SessionBuilder(QString databaseFile);
	QVector<Portfolio> buildPortfolios();
	QVector<Report*> buildReports(int idPortfolio);
	QMap<Asset*, int> buildPortfolioComposition(int idPortfolio);
};
