#ifndef CSOURCEITEM_H
#define CSOURCEITEM_H

#include "cprojectbase.h"
#include "codeeditorform.h"

#include <QMessageBox>
#include <QTabWidget>

class CSourceItem : public CProjectBase
{
	Q_OBJECT

public:
	CSourceItem(IProjectTreeViewItem* parent);
	~CSourceItem() override;

	// Member Getters
	QString sourceCode();

	// Member Setters
	void setSourceCode(QString sourceCode);

	CodeEditorForm* editor() const { return dynamic_cast<CodeEditorForm*>(m_editor); }

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	virtual bool serializeContent();
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;
	virtual bool deserializeContent();

	// IProjectTreeViewItem Interface Implmentation
	QString caption() const override;
	void openItemEvent(CProjectTabWidget* parent) override;
	void saveItemEvent() override;

private:
	// Attributes
	QString m_sourceCode;
};

#endif // CSOURCEITEM_H
