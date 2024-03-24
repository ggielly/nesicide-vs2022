#ifndef CATTRIBUTETABLE_H
#define CATTRIBUTETABLE_H

#include <stdint.h>

#include "cprojectbase.h"
#include "attributetableeditorform.h"

#include <QMessageBox>
#include <QTabWidget>

class CAttributeTable : public CProjectBase
{
	Q_OBJECT

public:
	CAttributeTable(IProjectTreeViewItem* parent);
	~CAttributeTable() override;

	// Member getters
	QList<uint8_t>& getPalette();

	AttributeTableEditorForm* editor() { return dynamic_cast<AttributeTableEditorForm*>(m_editor); }

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

	// IProjectTreeViewItem Interface Implmentation
	void openItemEvent(CProjectTabWidget* parent) override;
	void saveItemEvent() override;
	bool canChangeName() override { return true; }
	bool onNameChanged(QString newName) override;

private:
	QList<uint8_t> m_palette;
};

#endif // CATTRIBUTETABLE_H
