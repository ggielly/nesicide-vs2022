#include "cbinaryfilemodel.h"

#include "cnesicideproject.h"
#include "model/projectsearcher.h"

CBinaryFileModel::CBinaryFileModel()
	: CSubModel()
{
}

QList<QUuid> CBinaryFileModel::getUuids() const
{
	if (m_pNesicideProject == nullptr)
		return QList<QUuid>();

	return ProjectSearcher::findUuidsOfType<CBinaryFile>(m_pNesicideProject);
}

QString CBinaryFileModel::getName(const QUuid& uuid) const
{
	return getFileName(uuid);
}


QString CBinaryFileModel::getFileName(const QUuid& uuid) const
{
	CBinaryFile* file = ProjectSearcher::findItemByUuid<CBinaryFile>(m_pNesicideProject, uuid);
	return file->caption();
}


QUuid CBinaryFileModel::addExistingBinaryFile(const QString& path)
{
	if (m_pNesicideProject == nullptr)
		return QUuid();

	QDir dir(QDir::currentPath());

	CBinaryFiles* binaryFiles = m_pNesicideProject->getProject()->getBinaryFiles();

	auto pBinaryFile = new CBinaryFile(binaryFiles);
	pBinaryFile->setName(dir.fromNativeSeparators(dir.relativeFilePath(path)));
	pBinaryFile->setPath(dir.fromNativeSeparators(dir.relativeFilePath(path)));
	pBinaryFile->deserializeContent();

	binaryFiles->getBinaryFileList().append(pBinaryFile);
	binaryFiles->appendChild(pBinaryFile);

	emit binaryFileAdded(pBinaryFile->uuid());
	return pBinaryFile->uuid();
}

void CBinaryFileModel::removeBinaryFile(const QUuid& uuid)
{
	if (m_pNesicideProject == nullptr)
		return;

	CBinaryFile* file = ProjectSearcher::findItemByUuid<CBinaryFile>(m_pNesicideProject, uuid);
	if (file == nullptr)
		return;

	CBinaryFiles* binaryFiles = m_pNesicideProject->getProject()->getBinaryFiles();
	binaryFiles->removeChild(file);
	binaryFiles->getBinaryFileList().removeAll(file);
	m_pNesicideProject->setDirty(true);
	delete file;

	emit binaryFileRemoved(uuid);
}
