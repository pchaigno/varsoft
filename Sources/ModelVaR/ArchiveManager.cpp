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
void ArchiveManager::addPortfolios(QVector<Portfolio*>& portfolios) {
	foreach(Portfolio* portfolio, portfolios) {
		this->portfolios.append(portfolio);
	}
}

/**
 * @brief Accessor to the portfolios.
 * @return The portfolios from the archive.
 */
QVector<Portfolio*> ArchiveManager::getPortfolios() const {
	return this->portfolios;
}
