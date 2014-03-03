#pragma once
#include "IImportStrategie.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT ImportData : public IImportStrategie
{
public:
	virtual void import(const QString name, const QString file, const QString origin, const QDateTime firstDate, const QDateTime lastDate) const;
};
