#pragma once

#include "ArchiveManager.h"
#include "Portfolio.h"
#include "SessionSaver.h"
#include <QJsonDocument>
#include "ModelVaR_global.h"
#include "ImportException.h"
#include <QDir>

class MODELVARSHARED_EXPORT ImportManager: public ArchiveManager {
public:
	ImportManager(QString archivePath);
	void importArchive();

private:
	void readDescriptor(QuaZipFile& file);
};
