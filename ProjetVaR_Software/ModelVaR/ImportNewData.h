#pragma once
#include "IImportStrategie.h"
#include "ModelVaR_global.h"

class MODELVARSHARED_EXPORT ImportNewData : public IImportStrategie{
public:
	virtual void import(const QString file, const QString name, const QDateTime firstDate, const QDateTime lastDate) const;
};
