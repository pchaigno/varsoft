#include "RInterface.h"

/**
 * @brief Call the R script for the correlation test.
 * @param portfolio The portfolio to test.
 * @return True if the test succeed.
 */
bool RInterface::checkCorrelation(const Portfolio& portfolio) {
	// TODO
	return false;
}

/**
 * @brief Call the R script for the square correlation test.
 * @param portfolio The portfolio to test.
 * @return True if the test succeed.
 */
bool RInterface::checkSquareCorrelation(const Portfolio& portfolio) {
	// TODO
	return false;
}

/**
 * @brief Call the R script to compute the GARCH model of a portfolio.
 * @param portfolio The portfolio.
 * @return The GARCH model.
 */
GarchModel RInterface::computeGarchModel(const Portfolio& portfolio) {
	// TODO
	return GarchModel();
}
