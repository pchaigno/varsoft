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
#pragma once

#include <QString>
#include "Asset.h"
#include "SessionBuilder.h"

class AssetsFactory {
private:
	static AssetsFactory* instance;
	QMap<QString, Asset*> assets;

public:
	Asset* retrieveAsset(QString name);
	static AssetsFactory* getInstance() {
		if(instance == NULL) {
			instance = new AssetsFactory();
		}
		return instance;
	}

private:
	AssetsFactory();
};
