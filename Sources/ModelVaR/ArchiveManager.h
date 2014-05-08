#pragma once

#include <QString>
#include "quazip.h"
#include "Portfolio.h"
#include "ModelVaR_global.h"
#include "quazipfile.h"

class MODELVARSHARED_EXPORT ArchiveManager {
protected:
	QString archivePath;
	QVector<Portfolio*> portfolios;

public:
	ArchiveManager(QString archivePath);
	void addPortfolios(QVector<Portfolio*>& portfolios);
	QVector<Portfolio*> getPortfolios() const;

protected:
	static void moveFile(QString& originPath, QString& destPath);
};
