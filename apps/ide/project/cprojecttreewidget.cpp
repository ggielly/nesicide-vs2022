#include "cprojecttreewidget.h"

#include "model/cattributemodel.h"
#include "model/cbinaryfilemodel.h"
#include "model/ccartridgemodel.h"
#include "model/cfiltermodel.h"
#include "model/cgraphicsbankmodel.h"
#include "model/cprojectmodel.h"
#include "model/csourcefilemodel.h"
#include "model/ctilestampmodel.h"
#include "model/cmusicmodel.h"
#include "model/iuuidvisitor.h"

//--------------------------------------------------------------------------------------
// Helper classes
//--------------------------------------------------------------------------------------

// Extracts relevant data for tree node display.
class NodeDataReader : public IUuidVisitor
{
public:
	NodeDataReader(CProjectModel* project)
		: project(project)
	{
	}

	CProjectModel* project;
	QString name;
	QIcon icon;
	QString toolTip;

	// Unknown item. Display uuid and a question mark as icon.
	void visit(CUuid& d) override
	{
		name = d.uuid.toString();
		toolTip = QString();
		icon = QIcon(); // TODO Question mark?
	}

	void visit(CAttributeUuid& d) override
	{
		CAttributeModel* model = project->getAttributeModel();
		name = model->getName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/RR_page_white.png");
	}

	void visit(CBinaryFileUuid& d) override
	{
		CBinaryFileModel* model = project->getBinaryFileModel();
		name = model->getFileName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/RR_page_white.png");
	}

	void visit(CFilterUuid& d) override
	{
		CFilterModel* model = project->getFilterModel();
		name = model->getFilterName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/folder_closed.png");
	}

	void visit(CGraphicsBankUuid& d) override
	{
		CGraphicsBankModel* model = project->getGraphicsBankModel();
		name = model->getName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/RR_graphics_bank.png");
	}

	void visit(CSourceFileUuid& d) override
	{
		CSourceFileModel* model = project->getSourceFileModel();
		name = model->getFileName(d.uuid);
		toolTip = model->getRelativePath(d.uuid);
		icon = QIcon(":/resources/RR_page_asm.png");
	}

	void visit(CTileStampUuid& d) override
	{
		CTileStampModel* model = project->getTileStampModel();
		name = model->getName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/RR_page_white.png");
	}

	void visit(CMusicFileUuid& d) override
	{
		CMusicModel* model = project->getMusicModel();
		name = model->getName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/RR_page_white.png");
	}

	void visit(CChrRomUuid& d) override
	{
		CCartridgeModel* model = project->getCartridgeModel();
		name = model->getName(d.uuid);
		toolTip = QString();
		icon = QIcon(":/resources/RR_page_white.png");
	}

	void visit(CPrgRomUuid& d) override
	{
		CCartridgeModel* model = project->getCartridgeModel();
		name = model->getName(d.uuid);
		icon = QIcon(":/resources/RR_page_white.png");
	}
};

//--------------------------------------------------------------------------------------
// CProjectTreeWidget implementation
//--------------------------------------------------------------------------------------

CProjectTreeWidget::CProjectTreeWidget(QWidget* parent) :
	QTreeWidget(parent)
{
}

QUuid CProjectTreeWidget::getUuidAt(const QPoint& pos)
{
	return getUuidOf(this->itemAt(pos));
}

QUuid CProjectTreeWidget::getUuidOf(const QTreeWidgetItem* item)
{
	if (item == nullptr)
		return QUuid();

	return item->data(0, Qt::UserRole).toString();
}

bool CProjectTreeWidget::containsUuid(const QUuid& uuid)
{
	return findTreeWidgetItem(uuid) != nullptr;
}

void CProjectTreeWidget::setCurrentUuid(const QUuid& uuid)
{
	QTreeWidgetItem* item = findTreeWidgetItem(uuid);
	if (item != nullptr)
	{
		this->setCurrentItem(item);
	}
}

void CProjectTreeWidget::addItem(CProjectModel* project, const QUuid& uuid, const QUuid& parentUuid)
{
	QTreeWidgetItem* item = buildNodeFromUuid(project, uuid);

	QTreeWidgetItem* parentItem = findTreeWidgetItem(parentUuid);
	if (parentItem == nullptr)
		this->addTopLevelItem(item);
	else
		parentItem->addChild(item);
}

void CProjectTreeWidget::setParent(const QUuid& child, const QUuid& parent)
{
	QTreeWidgetItem* childItem = findTreeWidgetItem(child);
	QTreeWidgetItem* parentItem = findTreeWidgetItem(parent);

	if (parentItem == nullptr || childItem == nullptr)
		return;

	if (childItem->parent())
	{
		childItem->parent()->removeChild(childItem);
	}
	else
	{
		this->takeTopLevelItem(this->indexOfTopLevelItem(childItem));
	}

	parentItem->addChild(childItem);
}

void CProjectTreeWidget::removeItem(const QUuid& uuid)
{
	delete findTreeWidgetItem(uuid);
}

QTreeWidgetItem* CProjectTreeWidget::buildNodeFromUuid(CProjectModel* project, const QUuid& uuid)
{
	NodeDataReader visitor(project);
	project->visitDataItem(uuid, visitor);

	auto item = new QTreeWidgetItem();
	item->setText(0, visitor.name);
	item->setIcon(0, visitor.icon);
	item->setToolTip(0, visitor.toolTip);
	item->setData(0, Qt::UserRole, QVariant(uuid));

	return item;
}

QTreeWidgetItem* CProjectTreeWidget::findTreeWidgetItem(const QUuid& uuid)
{
	QTreeWidgetItemIterator it(this);
	while (*it)
	{
		if (getUuidOf(*it) == uuid)
			return *it;
		++it;
	}

	return nullptr;
}
