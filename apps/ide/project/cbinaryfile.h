#ifndef CBINARYFILE_H
#define CBINARYFILE_H

#include "cprojectbase.h"
#include "ichrrombankitem.h"

#include <QMessageBox>

class CBinaryFile : public CProjectBase,
                    public IChrRomBankItem
{
	Q_OBJECT

public:
	CBinaryFile(IProjectTreeViewItem* parent);
	~CBinaryFile() override;

	// Member getters.
	QByteArray getBinaryData();
	QImage getBinaryImage();

	void getSize(int* xSize, int* ySize)
	{
		(*xSize) = m_xSize;
		(*ySize) = m_ySize;
	}

	// Member setters.
	void setBinaryData(const QByteArray& newBinaryData);

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;
	virtual bool deserializeContent();

	// IProjectTreeViewItem Interface Implmentation
	QString caption() const override;

	void openItemEvent(CProjectTabWidget*) override
	{
	}

	// ICenterWidgetItem Interface Implementation

	// IChrRomBankItem Interface Implementation
	int getChrRomBankItemSize() override;
	QByteArray getChrRomBankItemData() override;
	QIcon getChrRomBankItemIcon() override;
	QImage getChrRomBankItemImage() override;

	QString getItemType() override
	{
		return "Binary File";
	}

private:
	// Attributes
	QByteArray m_binaryData;
	int m_xSize;
	int m_ySize;
};

#endif // CBINARYFILE_H
