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
#include "ArchiveManager.h"

/**
 * @brief Constructor
 * @param archivePath The path to the archive file.
 */
ArchiveManager::ArchiveManager(QString archivePath) {
	this->archivePath = archivePath;
}

/**
 * @brief Adds the specified portfolio to the archive.
 * @param portfolios The portfolios to add.
 */
void ArchiveManager::addPortfolios(QList<Portfolio*>& portfolios) {
	foreach(Portfolio* portfolio, portfolios) {
		this->portfolios.append(portfolio);
	}
}

/**
 * @brief Accessor to the portfolios.
 * @return The portfolios from the archive.
 */
QList<Portfolio*> ArchiveManager::getPortfolios() const {
	return this->portfolios;
}
