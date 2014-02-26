#pragma once
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QString>
#include "Asset.h"
#include "ModelVaR_global.h"
class MODELVARSHARED_EXPORT IImportStrategie
{
public:
	virtual void import(QString s) const =0;
};

