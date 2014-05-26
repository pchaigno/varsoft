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
#include "AssetsFactory.h"

/**
 * @brief Singleton definition. Mandatory.
 */
AssetsFactory* AssetsFactory::instance = NULL;

/**
 * @brief Private constructor.
 */
AssetsFactory::AssetsFactory() {
	this->assets = SessionBuilder::getInstance()->buildAssets();
}

/**
 * @brief Retrieves an asset by its name.
 * @param name The name of the asset to retrieve.
 * @return A pointer to the asset or null if the asset doesn't exist.
 */
Asset* AssetsFactory::retrieveAsset(QString name) {
	if(!this->assets.contains(name) || this->assets[name]==NULL) {
		this->assets[name] = SessionBuilder::getInstance()->buildAsset(name);
	}
	return this->assets[name];
}
