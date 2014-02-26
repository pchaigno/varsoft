#pragma once
#include "IImportStrategie.h"
class ImportData : public IImportStrategie
{
public:
	virtual void import(QString s) const;
};
