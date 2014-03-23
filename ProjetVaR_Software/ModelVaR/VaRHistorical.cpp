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
#include "VaRHistorical.h"

/**
 * @brief Constructor
 * @param portfolio The portfolio to apply the algorithm to.
 * @param risk The risk level.
 */
VaRHistorical::VaRHistorical(const Portfolio& portfolio, double risk):
	VaRAlgorithm(portfolio, risk) {

}

/**
 * @brief Computes the VaR using the historical method.
 * @param timeHorizon The time horizon to calculate the VaR.
 * @return The VaR for this portfolio using the historical method.
 */
double VaRHistorical::execute(QDateTime timeHorizon) const {
	// TODO
	return 0;
}
