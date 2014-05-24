#include "TestMathFunctions.h"

TestMathFunctions::TestMathFunctions() {}

/**
 * @brief Checks several computation of the inverse of the normal cumulative distribution function
 */
void TestMathFunctions::testNormalCDFInverse() {
	QCOMPARE(MathFunctions::normalCDFInverse(0.2), -0.8414567173548);
	QCOMPARE(MathFunctions::normalCDFInverse(0.4), -0.2529332678266);
	QCOMPARE(MathFunctions::normalCDFInverse(0.6), 0.2529332678266);
	QCOMPARE(MathFunctions::normalCDFInverse(0.8), 0.8414567173548);
	QCOMPARE(MathFunctions::normalCDFInverse(0.95), 1.645211440144);
}

/**
 * @brief Checks that undefined domain values are actually not computed
 */
void TestMathFunctions::testNormalCDFInverseUndefined() {
	try {
		MathFunctions::normalCDFInverse(0.0);
	} catch(std::invalid_argument& e) {}

	try {
		MathFunctions::normalCDFInverse(1.0);
	} catch(std::invalid_argument& e) {}
}
