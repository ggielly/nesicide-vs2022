#ifndef CATTRIBUTETABLES_H
#define CATTRIBUTETABLES_H

#include "cattributetable.h"

#include <QInputDialog>
#include <QList>

class CAttributeTables : public CProjectBase
{
	Q_OBJECT

public:
	CAttributeTables(IProjectTreeViewItem* parent);
	~CAttributeTables() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	QList<CAttributeTable*>& getAttributeTableList() { return m_attributeTables; }

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

	// IProjectTreeViewItem Interface Implmentation
	QString caption() const override;

	void openItemEvent(CProjectTabWidget*) override
	{
	}

	// ICenterWidgetItem Interface Implementation

private:
	// Contained children
	QList<CAttributeTable*> m_attributeTables;
};

#endif // CATTRIBUTETABLES_H
