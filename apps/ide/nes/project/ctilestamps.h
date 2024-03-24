#ifndef CTILESTAMPS_H
#define CTILESTAMPS_H

#include "ctilestamp.h"

#include <QList>

class CTileStamps : public CProjectBase
{
	Q_OBJECT

public:
	CTileStamps(IProjectTreeViewItem* parent);
	~CTileStamps() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	QList<CTileStamp*>& getTileStampList() { return m_tileStamps; }

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
	QList<CTileStamp*> m_tileStamps;
};

#endif // CTILESTAMPS_H
