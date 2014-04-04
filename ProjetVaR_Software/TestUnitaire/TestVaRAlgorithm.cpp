#include "TestVaRAlgorithm.h"

TestVaRAlgorithm::TestVaRAlgorithm(VaRAlgorithm * _algo){
	this->algo = _algo;
}

void TestVaRAlgorithm::testVaRAlgorithmRisk() {
	this->algo->execute(this->algo->getPortfolio().retrieveLastDate());
}
