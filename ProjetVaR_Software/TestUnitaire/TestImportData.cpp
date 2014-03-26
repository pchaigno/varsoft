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
#include "TestImportData.h"

/**
* @brief Initializes an asset for the tests.
*/
TestImportData::TestImportData() {
	TestImportData::stockName = "Gogole";
	TestImportData::firstDate = "2014-01-02";
	TestImportData::lastDate = "2014-01-01";
	TestImportData::origin = "Yahoo";
}

/**
* @brief Checks that the firstDate and the lastDate of the generated file correspond to the params
*/
void TestImportData::testDates() {
	
}
