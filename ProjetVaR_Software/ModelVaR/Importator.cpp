#include "Importator.h"

Importator::Importator(IImportStrategie& strategy): strategy(strategy){}

void Importator::execute(QString s)
{
	strategy.import(s);
}

