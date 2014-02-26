#pragma once
#include "IImportStrategie.h"

class ImportNewData : public IImportStrategie{
public:
	virtual void import(QString s) const;
};
