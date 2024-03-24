#ifndef CBINARYFILES_H
#define CBINARYFILES_H

#include "cprojectbase.h"
#include "cbinaryfile.h"

#include <QList>
#include <QMenu>
#include <QFileDialog>

class CBinaryFiles : public CProjectBase
{
	Q_OBJECT

public:
	CBinaryFiles(IProjectTreeViewItem* parent);
	~CBinaryFiles() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	QList<CBinaryFile*>& getBinaryFileList() { return m_binaryFiles; }

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
	QList<CBinaryFile*> m_binaryFiles;
};

#endif // CBINARYFILES_H
