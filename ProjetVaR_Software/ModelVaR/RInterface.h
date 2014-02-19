#ifndef H_RINTERFACE
#define H_RINTERFACE

#include "Portfolio.h"
#include "GarchModel.h"

class RInterface {
public:
	static bool checkCorrelation(const Portfolio& portfolio);
	static bool checkSquareCorrelation(const Portfolio& portfolio);
	static GarchModel computeGarchModel(const Portfolio& portfolio);
};
#endif
