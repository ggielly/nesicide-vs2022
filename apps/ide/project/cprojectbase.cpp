#include "cprojectbase.h"

#include "cnesicideproject.h"

CProjectBase::CProjectBase()
{
	m_name = "";
	m_path = "";
	m_editor = nullptr;
	m_deleted = false;
	m_includeInBuild = true;
}

CProjectBase::~CProjectBase()
{
	if (m_editor)
	{
		delete m_editor;
	}
}

IProjectTreeViewItem* findProjectItem(QString uuid)
{
	IProjectTreeViewItemIterator iter(CNesicideProject::instance()->getProject());

	while (iter.current() != nullptr)
	{
		IProjectTreeViewItem* pItem = iter.current();

		if (pItem->uuid() == uuid)
		{
			return pItem;
		}

		iter.next();
	}

	return nullptr;
}

void CProjectBase::closeItemEvent()
{
	if (m_editor)
	{
		delete m_editor;
	}
	m_editor = nullptr;
}
