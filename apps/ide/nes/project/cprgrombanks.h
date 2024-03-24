#ifndef CPRGROMBANKS_H
#define CPRGROMBANKS_H

#include "cprojectbase.h"
#include "cprgrombank.h"

#include <QList>

class CPRGROMBanks : public CProjectBase
{
	Q_OBJECT

public:
	CPRGROMBanks(IProjectTreeViewItem* parent);
	~CPRGROMBanks() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	// Member Getters
	QList<CPRGROMBank*>& getPrgRomBanks() { return m_prgRomBanks; }

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
	QList<CPRGROMBank*> m_prgRomBanks;
};

#endif // CPRGROMBANKS_H
