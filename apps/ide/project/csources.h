#ifndef CSOURCES_H
#define CSOURCES_H

#include "cprojectbase.h"
#include "csourceitem.h"

#include <QInputDialog>
#include <QList>

class CSources : public CProjectBase
{
	Q_OBJECT

public:
	CSources(IProjectTreeViewItem* parent);
	~CSources() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	CSourceItem* addSourceFile(QString fileName);
	void removeSourceFile(CSourceItem* item);

	// Member Getters
	QList<CSourceItem*>& getSourceItems() { return m_sourceItems; }

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
	QList<CSourceItem*> m_sourceItems;
};

#endif // CSOURCES_H
