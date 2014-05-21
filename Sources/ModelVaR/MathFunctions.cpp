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
#include "MathFunctions.h"

MathFunctions::MathFunctions() {}

/**
 * @brief MathFunctions::rationalApproximation computes a rational approximation
 * Intermediate function to perfom computation of the inverse of the normal cumulative
 * function
 * @param t The value on which the approximation is applied
 * @return The approximated value
 */
double MathFunctions::rationalApproximation(double t) {
	// Abramowitz and Stegun formula 26.2.23.
	// The absolute value of the error should be less than 4.5 e-4.
	double c[] = {2.515517, 0.802853, 0.010328};
	double d[] = {1.432788, 0.189269, 0.001308};
	return t - ((c[2]*t + c[1])*t + c[0]) /
			(((d[2]*t + d[1])*t + d[0])*t + 1.0);
}

/**
 * @brief MathFunctions::normalCDFInverse computes the inverse of the normal cumulative distribution function
 * @param p The value on which is applied the function
 * @return The inverse of the normal cumulative distribution function value
 */
double MathFunctions::normalCDFInverse(double p) {
	if (p <= 0.0 || p >= 1.0) {
		QString os;
		os = "Invalid input argument (" + QString::number(p) + "); must be larger than 0 but less than 1.";
		throw std::invalid_argument(os.toStdString().c_str());
	}

	if (p < 0.5) {
		// F^-1(p) = - G^-1(p)
		return -rationalApproximation(qSqrt(-2.0*qLn(p)));
	}
	else {
		// F^-1(p) = G^-1(1-p)
		return rationalApproximation(qSqrt(-2.0*qLn(1-p)));
	}
}
