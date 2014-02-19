#ifndef H_PORTFOLIO
#define H_PORTFOLIO

#include <QString>
#include <QVector>
#include "Report.h"
#include <QMap>
#include "Asset.h"
#include <climits>
#include <QDateTime>


class Portfolio {
private:
    QString name;
	Portfolio* parent;
    QMap<Asset*, int> assets;
    QVector<Report> reports;

public:
	Portfolio(const Portfolio& portfolio);
    Portfolio(Portfolio* parent, QString name, QMap<Asset*, int>& assets, QVector<Report>& reports);
    Portfolio(QString name, QMap<Asset*, int>& assets, QVector<Report>& reports);

    QString getName() const;
    QVector<Report> getReports() const;
    void changeName(QString name);

    QDateTime retrieveFirstDate() const;
    QDateTime retrieveLastDate() const;

	Portfolio& operator=(const Portfolio& portfolio);
};
#endif
