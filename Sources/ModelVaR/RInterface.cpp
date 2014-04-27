/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
