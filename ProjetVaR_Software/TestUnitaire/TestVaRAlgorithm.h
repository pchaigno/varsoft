#include "VaRAlgorithm.h"
#include "VaRHistorical.h"

class TestVaRAlgorithm {
private:
	VaRAlgorithm * algo;

public:
	TestVaRAlgorithm(VaRAlgorithm * _algo);
	void testVaRAlgorithmRisk();
};
