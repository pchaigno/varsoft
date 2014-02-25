#ifndef IMPORTNEWDATA_H
#define IMPORTNEWDATA_H
#include "IImportStrategie.h"

class ImportNewData : public IImportStrategie{
public:
	virtual void import();
}
#endif // IMPORTNEWDATA_H
