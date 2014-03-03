#pragma once
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QString>
#include "Asset.h"
#include "ModelVaR_global.h"
class MODELVARSHARED_EXPORT IImportStrategie
{
public:
	virtual void import(const QString name, const QString file, const QString origin,const QDateTime firstDate, const QDateTime lastDate) const =0;
};

