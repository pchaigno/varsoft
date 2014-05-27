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
#include "ImportManager.h"

ImportManager::ImportManager(QString archivePath): ArchiveManager(archivePath) {

}

/**
 * @brief Imports the portfolios from the archive.
 * @return True if the portfolios from the archive was imported successfully.
 */
void ImportManager::importArchive() {
	QuaZip zip(this->archivePath);
	if(!zip.open(QuaZip::mdUnzip)) {
		throw ImportException("Cannot open archive.");
	}

	// Creates folders:
	QDir resourcesFolder(SQLiteManager::getSessionFolder() + QDir::separator() + "Resources");
	resourcesFolder.mkdir("Assets");
	resourcesFolder.mkdir("Reports");

	// Extracts files (assets and reports):
	QuaZipFile file(&zip);
	bool containsDescriptor = false;
	for(bool f=zip.goToFirstFile(); f; f=zip.goToNextFile()) {
		QString filePath = file.getActualFileName();

		// Skips folder if encountered:
		if(filePath[filePath.size()-1] == '/') {
			continue;
		}

		if(!file.open(QIODevice::ReadOnly)) {
			throw ImportException("Cannot open "+file.getActualFileName()+" from archive.");
		}

		if(filePath == "portfolios.json") {
		// Loads the descriptor file (portfolios in memory and assets in database).
			this->readDescriptor(file);
			containsDescriptor = true;
		} else {
		// Copies the files from the archive to the disk:
			QFile destFile(resourcesFolder.absolutePath() + QDir::separator() + filePath);
			if(!destFile.open(QIODevice::WriteOnly)) {
				throw ImportException("Cannot create file "+filePath+" in Resources.");
			}
			char c;
			while(file.getChar(&c) && destFile.putChar(c));
			destFile.close();
		}
		file.close();
	}

	// Throws an exception if the archive contains no descriptor:
	if(!containsDescriptor) {
		throw ImportException("No descriptor file in the archive.");
	}
	zip.close();
}

/**
 * @brief Imports/deserializes the portfolios from the archive.
 * The assets are directly saved in the database.
 * Sets the portfolios attribute of the manager.
 * @param data The JSON document as an array of bytes.
 */
void ImportManager::readDescriptor(QuaZipFile& file) {
	QByteArray data = file.readAll();
	QJsonDocument document = QJsonDocument::fromJson(data);
	QJsonObject json = document.object();

	// Retrieves the assets:
	QJsonArray assetsJson = json["assets"].toArray();
	for(int i=0; i<assetsJson.size(); i++) {
		const QJsonObject assetJson = assetsJson[i].toObject();
		Asset* asset = new Asset(assetJson);
		SessionSaver::getInstance()->saveAsset(*asset);
	}

	// Retrieves the portfolios:
	QJsonArray portfoliosJson = json["portfolios"].toArray();
	QMap<QString, Portfolio*> deserializedPortfolios;
	this->portfolios.clear();
	for(int i=0; i<portfoliosJson.size(); i++) {
		const QJsonObject portfolioJson = portfoliosJson[i].toObject();
		Portfolio* portfolio = new Portfolio(portfolioJson, deserializedPortfolios);
		this->portfolios.append(portfolio);
	}
}
