#ifndef CGRAPHICSBANK_H
#define CGRAPHICSBANK_H

#include "cprojectbase.h"
#include "graphicsbankeditorform.h"

#include <QMessageBox>
#include <QMenu>

class CGraphicsBank : public CProjectBase
{
	Q_OBJECT

public:
	CGraphicsBank(IProjectTreeViewItem* parent);
	~CGraphicsBank() override;

	// Member getters
	QList<IChrRomBankItem*> getGraphics();
	uint32_t getSize() const;

	GraphicsBankEditorForm* editor() const { return dynamic_cast<GraphicsBankEditorForm*>(m_editor); }
	void exportAsPNG();

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

	// IProjectTreeViewItem Interface Implmentation
	QString caption() const override;
	void openItemEvent(CProjectTabWidget* tabWidget) override;
	void saveItemEvent() override;

	bool canChangeName() override
	{
		return true;
	}

	bool onNameChanged(QString newName) override;

private:
	// Attributes
	QList<IChrRomBankItem*> m_bankItems;
	uint32_t m_bankSize;
};

#endif // CGRAPHICSBANK_H
