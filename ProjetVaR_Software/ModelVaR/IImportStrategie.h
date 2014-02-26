#pragma once
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QString>
#include "Asset.h"
class IImportStrategie
{
public:
	virtual void import(QString s) const =0;
};

