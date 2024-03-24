#ifndef CGRAPHICSBANKS_H
#define CGRAPHICSBANKS_H

#include "cprojectbase.h"
#include "cgraphicsbank.h"

#include <QList>
#include <QInputDialog>

class CGraphicsBanks : public CProjectBase
{
	Q_OBJECT

public:
	CGraphicsBanks(IProjectTreeViewItem* parent);
	~CGraphicsBanks() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	QList<CGraphicsBank*>& getGraphicsBanks() { return m_graphicsBanks; }

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

	// IProjectTreeViewItem Interface Implmentation
	QString caption() const override
	{
		return QString("Graphics Banks");
	}

	void openItemEvent(CProjectTabWidget*) override
	{
	}

	// ICenterWidgetItem Interface Implementation

private:
	// Contained children
	QList<CGraphicsBank*> m_graphicsBanks;
};

#endif // CGRAPHICSBANKS_H
