#include "ctilestampmodel.h"

#include "cnesicideproject.h"
#include "model/projectsearcher.h"

CTileStampModel::CTileStampModel()
	: CSubModel()
{
}

QList<QUuid> CTileStampModel::getUuids() const
{
	if (m_pNesicideProject == nullptr)
		return QList<QUuid>();

	return ProjectSearcher::findUuidsOfType<CTileStamp>(m_pNesicideProject);
}

QString CTileStampModel::getName(const QUuid& uuid) const
{
	if (m_pNesicideProject == nullptr)
		return QString();

	CTileStamp* tile = ProjectSearcher::findItemByUuid<CTileStamp>(m_pNesicideProject, uuid);
	return tile->caption();
}


QUuid CTileStampModel::newTileStamp(const QString& name)
{
	if (m_pNesicideProject == nullptr)
		return QUuid();

	CTileStamps* pTileStamps = m_pNesicideProject->getProject()->getProjectPrimitives()->getTileStamps();
	auto pTileStamp = new CTileStamp(pTileStamps);
	pTileStamp->setName(name);
	pTileStamps->getTileStampList().append(pTileStamp);
	pTileStamps->appendChild(pTileStamp);

	m_pNesicideProject->setDirty(true);
	emit tileStampAdded(pTileStamp->uuid());
	return pTileStamp->uuid();
}

QUuid CTileStampModel::newScreen(const QString& name)
{
	if (m_pNesicideProject == nullptr)
		return QUuid();

	CTileStamps* pTileStamps = m_pNesicideProject->getProject()->getProjectPrimitives()->getTileStamps();
	auto pTileStamp = new CTileStamp(pTileStamps);
	pTileStamp->setName(name);
	pTileStamp->setSize(256, 240);
	pTileStamps->getTileStampList().append(pTileStamp);
	pTileStamps->appendChild(pTileStamp);

	m_pNesicideProject->setDirty(true);
	emit tileStampAdded(pTileStamp->uuid());
	return pTileStamp->uuid();
}

void CTileStampModel::deleteTileStamp(const QUuid& uuid)
{
	if (m_pNesicideProject == nullptr)
		return;

	CTileStamp* pTileStamp = ProjectSearcher::findItemByUuid<CTileStamp>(m_pNesicideProject, uuid);
	if (pTileStamp == nullptr)
		return;

	m_pNesicideProject->getProject()->getProjectPrimitives()->getTileStamps()->removeChild(pTileStamp);
	m_pNesicideProject->getProject()->getProjectPrimitives()->getTileStamps()->getTileStampList().removeAll(pTileStamp);
	m_pNesicideProject->setDirty(true);
	delete pTileStamp;

	emit tileStampRemoved(uuid);
}

CDesignerEditorBase* CTileStampModel::createEditorWidget(const QUuid& uuid) const
{
	CTileStamp* tile = ProjectSearcher::findItemByUuid<CTileStamp>(m_pNesicideProject, uuid);
	if (tile == nullptr)
		return nullptr;

	int x, y;
	tile->getSize(&x, &y);
	auto editor = new TileStampEditorForm(tile->getTileData(), tile->getAttributeData(),
	                                      tile->getAttrTbl(), tile->getTileProperties(),
	                                      x, y, tile->getGridSetting(), tile);
	tile->setEditor(editor);
	return editor;
}
