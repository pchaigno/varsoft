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
 * @brief Constructor
 * @param _omega The omega coefficient
 * @param _alpha The alpha coefficient
 * @param _beta The beta coefficient
 */
GarchModel::GarchModel(double _omega, double _alpha, double _beta, QVector<double> _residuals, QVector<double> _stddev): omega(_omega), alpha(_alpha), beta(_beta), residuals(_residuals), stddev(_stddev) {}

/**
 * @brief Accessor to the omega coefficient
 * @return The omega coeffcient of the garch model
 */
double GarchModel::getOmega() const {return this->omega;}

/**
 * @brief Accessor to the alpha coefficient
 * @return The alpha coeffcient of the garch model
 */
double GarchModel::getAlpha() const {return this->alpha;}

/**
 * @brief Accessor to the beta coefficient
 * @return The beta coeffcient of the garch model
 */
double GarchModel::getBeta() const {return this->beta;}

QVector<double> GarchModel::getResiduals() const {
	return residuals;
}

QVector<double> GarchModel::getStddev() const {
	return stddev;

}
