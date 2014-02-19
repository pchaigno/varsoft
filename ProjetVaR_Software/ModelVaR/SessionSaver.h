#ifndef H_SESSIONSAVER
#define H_SESSIONSAVER

#include "SQLiteManager.h"
#include "Portfolio.h"
#include "Asset.h"
#include "Report.h"


class SessionSaver: public SQLiteManager {
private:
	static SessionSaver* instance;

public:
	void saveAsset(const Asset& asset);
    void saveSession(const QVector<Portfolio>& portfolios);
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
    void saveAssets(const QVector<Asset>& assets);
    void savePortfolios(const QVector<Portfolio>& portfolios);
    void saveReports(const Portfolio& portfolio, const QVector<Report>& reports);
};
#endif
