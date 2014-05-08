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
	QDir resourcesFolder("Resources");
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
			QFile destFile("Resources/"+filePath);
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
