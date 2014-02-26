#pragma once
#include "IImportStrategie.h"

class Importator
{
private:
	IImportStrategie& strategy;

public:
	Importator(IImportStrategie& strategy);

	void execute(QString s);

};
