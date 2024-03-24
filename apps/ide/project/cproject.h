#ifndef CPROJECT_H
#define CPROJECT_H

#include "cprojectbase.h"
#include "cprojectprimitives.h"
#include "csources.h"
#include "cbinaryfiles.h"
#include "cgraphicsbanks.h"
#include "csounds.h"

class CProject : public CProjectBase
{
	Q_OBJECT

public:
	CProject(IProjectTreeViewItem* parent);
	~CProject() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	CProjectPrimitives* getProjectPrimitives() { return m_pProjectPrimitives; }
	CSources* getSources() { return m_pSources; }
	CBinaryFiles* getBinaryFiles() { return m_pBinaryFiles; }
	CGraphicsBanks* getGraphicsBanks() { return m_pGraphicsBanks; }
	CSounds* getSounds() { return m_pSounds; }

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
	// Attributes

	// Contained children
	CProjectPrimitives* m_pProjectPrimitives;
	CSources* m_pSources;
	CBinaryFiles* m_pBinaryFiles;
	CGraphicsBanks* m_pGraphicsBanks;
	CSounds* m_pSounds;
};

#endif // CPROJECT_H
