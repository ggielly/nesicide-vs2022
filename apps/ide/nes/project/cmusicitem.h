#ifndef CMUSICITEM_H
#define CMUSICITEM_H

#include <stdint.h>

#include "cprojectbase.h"
#include "musiceditorform.h"

#include <QMessageBox>
#include <QTabWidget>

class CMusicItem : public CProjectBase
{
	Q_OBJECT

public:
	CMusicItem(IProjectTreeViewItem* parent);
	~CMusicItem() override;

	// Member Getters
	QByteArray musicData();

	// Member Setters
	void setMusicData(QByteArray musicData);

	music_editor_form* editor() { return dynamic_cast<music_editor_form*>(m_editor); }

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	virtual bool serializeContent();
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;
	virtual bool deserializeContent();

	// IProjectTreeViewItem Interface Implmentation
	void openItemEvent(CProjectTabWidget* parent) override;
	bool canChangeName() override { return true; }
	bool onNameChanged(QString newName) override;

	// CProjectBase Interface Implementation
	bool exportData() override;

private:
	QByteArray m_musicData;
};

#endif // CMUSICITEM_H
