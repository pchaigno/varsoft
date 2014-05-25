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

/**
 * @brief Tests the correlation calculation function. Compares the calculated values to the ones
 * calculated by R.
 */
void TestMathFunctions::testCorrelation() {
	QVector<double> a, b, c, d;
	a << 1 << 2 << 3;
	b << 1 << 2 << 4;
	c << 2.23 << 45.456 << 77.4;
	d << -32.14 << 234.2 << 0;
	QCOMPARE(MathFunctions::correlation(a,a), 1.0);
	QCOMPARE(MathFunctions::correlation(a,b), 0.981980506062);
	QCOMPARE(MathFunctions::correlation(b,c), 0.9619998241311);
	QCOMPARE(MathFunctions::correlation(c,d), 0.1959219137055);
	QCOMPARE(MathFunctions::correlation(b,d), -0.07928137235406);
}
