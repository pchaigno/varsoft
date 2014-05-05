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
	for(bool f=zip.goToFirstFile(); f; f=zip.goToNextFile()) {
		if(!file.open(QIODevice::ReadOnly)) {
			throw ImportException("Cannot open "+file.getActualFileName()+" from archive.");
		}
		QString filePath = file.getActualFileName();

		if(filePath == "portfolios.json") {
			this->readDescriptor(file);
		} else {
			QFile destFile("Resources\\"+filePath);
			if(!destFile.open(QIODevice::WriteOnly)) {
				throw ImportException("Cannot create file "+filePath+" in Resources.");
			}
			char c;
			while(file.getChar(&c) && destFile.putChar(c));
			destFile.close();
		}
		file.close();
	}
	zip.close();
}

/**
 * @brief Imports/deserializes the portfolios from the archive.
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
