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
#include "GarchModel.h"

/**
 * @brief Constructor of GarchModel
 * @param _omega The omega coefficient
 * @param _alpha The alpha coefficient
 * @param _beta The beta coefficient
 * @param _residuals The residuals
 */
GarchModel::GarchModel(double _omega, double _alpha, double _beta, QVector<double> _residuals): omega(_omega), alpha(_alpha), beta(_beta), residuals(_residuals) {}

/**
 * @brief Accessor to the omega coefficient
 * @return The omega coefficient of the Garch model
 */
double GarchModel::getOmega() const {
	return this->omega;
}

/**
 * @brief Accessor to the alpha coefficient
 * @return The alpha coefficient of the Garch model
 */
double GarchModel::getAlpha() const {
	return this->alpha;
}

/**
 * @brief Accessor to the beta coefficient
 * @return The beta coefficient of the Garch model
 */
double GarchModel::getBeta() const {
	return this->beta;
}

/**
 * @brief Accessor to the residuals
 * @return The residuals of the Garch model
 */
QVector<double> GarchModel::getResiduals() const {
	return this->residuals;
}
