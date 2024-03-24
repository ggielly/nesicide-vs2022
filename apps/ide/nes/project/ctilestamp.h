#ifndef CTILESTAMP_H
#define CTILESTAMP_H

#include <stdint.h>

#include "cprojectbase.h"
#include "tilestampeditorform.h"
#include "ichrrombankitem.h"
#include "cpropertylistmodel.h"

#include <QMessageBox>
#include <QTabWidget>

class CTileStamp : public CProjectBase, public IChrRomBankItem
{
	Q_OBJECT

public:
	CTileStamp(IProjectTreeViewItem* parent);
	~CTileStamp() override;

	// Member getters
	QByteArray getTileData();
	QByteArray getAttributeData();

	void getSize(int* xSize, int* ySize)
	{
		(*xSize) = m_xSize;
		(*ySize) = m_ySize;
	}

	QString getAttrTbl() { return m_attrTblUUID; }
	QImage getTileImage();
	QList<PropertyItem> getTileProperties() { return m_tileProperties; }
	bool getGridSetting() { return m_grid; }

	// Member setters
	void setSize(int xSize, int ySize)
	{
		m_xSize = xSize;
		m_ySize = ySize;
	}

	TileStampEditorForm* editor() { return dynamic_cast<TileStampEditorForm*>(m_editor); }

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	virtual bool serializeContent();
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;
	virtual bool deserializeContent();

	// IProjectTreeViewItem Interface Implmentation
	void openItemEvent(CProjectTabWidget* parent) override;
	void saveItemEvent() override;
	bool canChangeName() override { return true; }
	bool onNameChanged(QString newName) override;

	// IChrRomBankItem Interface Implementation
	int getChrRomBankItemSize() override;
	QByteArray getChrRomBankItemData() override;
	QIcon getChrRomBankItemIcon() override;
	QImage getChrRomBankItemImage() override;

	QString getItemType() override
	{
		return "Tile";
	}

private:
	QByteArray m_tile;
	QByteArray m_attr;
	int m_xSize;
	int m_ySize;
	QString m_attrTblUUID;
	QList<PropertyItem> m_tileProperties;
	bool m_grid;
};

#endif // CTILESTAMP_H
