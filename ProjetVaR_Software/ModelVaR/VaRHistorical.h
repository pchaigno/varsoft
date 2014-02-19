#ifndef H_VARHISTORICAL
#define H_VARHISTORICAL

#include "VaRAlgorithm.h"

class VaRHistorical: public VaRAlgorithm {
public:
	VaRHistorical(const Portfolio& portfolio, double risk);
    virtual double execute(QDateTime timeHorizon) const;
};

#endif
