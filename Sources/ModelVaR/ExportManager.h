#pragma once

#include "ArchiveManager.h"
#include <QVector>
#include "Portfolio.h"
#include "SessionBuilder.h"
#include <QJsonDocument>
#include "ModelVaR_global.h"
#include <QDirIterator>
#include "ExportException.h"

class MODELVARSHARED_EXPORT ExportManager: public ArchiveManager {
public:
	ExportManager(QString archivePath);
	void exportArchive(QVector<Portfolio*>& portfolios);
	void exportArchive();

private:
	QByteArray writeDescriptor();
	static void addToArchive(QDir folder, QuaZipFile& archivedFile);
};
