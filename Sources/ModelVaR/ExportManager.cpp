#include "ExportManager.h"

ExportManager::ExportManager(QString archivePath): ArchiveManager(archivePath) {

}

/**
 * @brief Exports the portfolios to the archive.
 * @param porfolios The portfolios to export.
 */
void ExportManager::exportArchive(QVector<Portfolio*>& portfolios) {
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
	QByteArray data = writeDescriptor();
	if(!archivedFile.open(QIODevice::WriteOnly, QuaZipNewInfo("portfolios.json"))) {
		throw ExportException("Cannot create descriptor file in archive.");
	}
	archivedFile.write(data);
	archivedFile.close();
	addToArchive(QDir("Resources\\Reports"), archivedFile);
	addToArchive(QDir("Resources\\Assets"), archivedFile);

	zip.close();
	if(zip.getZipError() != 0) {
		throw ExportException("Error while archiving ("+QString::number(zip.getZipError())+").");
	}
}

void ExportManager::addToArchive(QDir folder, QuaZipFile& archivedFile) {
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
		QString filePathInArchive = filePath;
		filePathInArchive.remove(0, QDir("Resources").absolutePath().size()+1); // Removes 'Resources/'
		if(!archivedFile.open(QIODevice::WriteOnly, QuaZipNewInfo(filePathInArchive))) {
			throw ExportException("Cannot create file "+filePathInArchive+" in archive.");
		}
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
