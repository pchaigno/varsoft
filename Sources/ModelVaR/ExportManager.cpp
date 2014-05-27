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
#include "ExportManager.h"

ExportManager::ExportManager(QString archivePath): ArchiveManager(archivePath) {

}

/**
 * @brief Exports the portfolios to the archive.
 * @param porfolios The portfolios to export.
 */
void ExportManager::exportArchive(QList<Portfolio*> portfolios) {
	this->addPortfolios(portfolios);
	this->exportArchive();
}

/**
 * @brief Exports the portfolios to the archive.
 * The portfolios must have been sets before with addPortfolios.
 */
void ExportManager::exportArchive() {
	QuaZip zip(this->archivePath);
	if(!zip.open(QuaZip::mdCreate)) {
		throw ExportException("Cannot create archive "+this->archivePath+".");
	}

	QuaZipFile archivedFile(&zip);

	// Adds the descriptor file in the archive:
	QByteArray data = writeDescriptor();
	if(!archivedFile.open(QIODevice::WriteOnly, QuaZipNewInfo("portfolios.json"))) {
		throw ExportException("Cannot create descriptor file in archive.");
	}
	archivedFile.write(data);
	archivedFile.close();

	// Adds the reports and assets' files to the archive:
	QDir resourcesFolder(SQLiteManager::getSessionFolder() + QDir::separator() + "Resources");
	addToArchive(resourcesFolder, "Reports", archivedFile);
	addToArchive(resourcesFolder, "Assets", archivedFile);

	zip.close();
	if(zip.getZipError() != 0) {
		throw ExportException("Error while archiving ("+QString::number(zip.getZipError())+").");
	}
}

/**
 * @brief Adds the content of a folder to the archive.
 * @param resourcesFolder Resources' folder.
 * @param folderName Folder to add to the archive.
 * @param archivedFile The archive file opened with QuaZip.
 */
void ExportManager::addToArchive(QDir resourcesFolder, QString folderName, QuaZipFile& archivedFile) {
	QDir folder = resourcesFolder.absolutePath() + QDir::separator() + folderName;
	QDirIterator it(folder.absolutePath());
	while(it.hasNext()) {
		QString filePath = it.next();
		QString filename = filePath;
		filename.remove(0, folder.absolutePath().size()+1);
		if(filename=="." || filename=="..") {
			continue;
		}
		QFile file(filePath);
		if(!file.open(QIODevice::ReadOnly)) {
			throw ExportException("Cannot open file "+filePath+".");
		}

		// Creates the file in the archive:
		QString filePathInArchive = filePath;
		filePathInArchive.remove(0, resourcesFolder.absolutePath().size()+1); // Removes '[..]/Resources/'.
		if(!archivedFile.open(QIODevice::WriteOnly, QuaZipNewInfo(filePathInArchive))) {
			throw ExportException("Cannot create file "+filePathInArchive+" in archive.");
		}

		// Writes the file's content:
		char c;
		while(file.getChar(&c) && archivedFile.putChar(c));
		archivedFile.close();
		file.close();
	}
}

/**
 * @brief Writes the JSON document containing all the objects
 * (portfolios, assets and reports) serialized.
 */
QByteArray ExportManager::writeDescriptor() {
	// Serializes the assets:
	QList<Asset*> assets = SessionBuilder::getInstance()->buildAssets().values();
	QJsonObject json;
	QJsonArray assetsJson;
	foreach(Asset* asset, assets) {
		assetsJson.append(asset->toJSON());
	}
	json["assets"] = assetsJson;

	// Serializes the portfolios:
	QJsonArray portfoliosJson;
	foreach(Portfolio* portfolio, this->portfolios) {
		portfoliosJson.append(portfolio->toJSON());
	}
	json["portfolios"] = portfoliosJson;

	QJsonDocument document = QJsonDocument(json);
	return document.toJson();
}
