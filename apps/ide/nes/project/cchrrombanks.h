#ifndef CCHRROMBANKS_H
#define CCHRROMBANKS_H

#include "cprojectbase.h"
#include "cchrrombank.h"

#include <QList>

class CCHRROMBanks : public CProjectBase
{
	Q_OBJECT

public:
	CCHRROMBanks(IProjectTreeViewItem* parent);
	~CCHRROMBanks() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	// Member Getters
	QList<CCHRROMBank*>& getChrRomBanks() { return m_chrRomBanks; }

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
	QList<CCHRROMBank*> m_chrRomBanks;
};

#endif // CCHRROMBANKS_H
