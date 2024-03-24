#ifndef CSOUNDS_H
#define CSOUNDS_H

#include "cprojectbase.h"
#include "cmusics.h"

#include <QString>

class CSounds : public CProjectBase
{
	Q_OBJECT

public:
	CSounds(IProjectTreeViewItem* parent);
	~CSounds() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	CMusics* getMusics() { return m_pMusics; }

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
	CMusics* m_pMusics;
};

#endif // CSOUNDS_H
