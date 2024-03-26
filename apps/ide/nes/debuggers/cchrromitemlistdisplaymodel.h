#ifndef CCHRROMITEMLISTDISPLAYMODEL_H
#define CCHRROMITEMLISTDISPLAYMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "ichrrombankitem.h"
#include "iprojecttreeviewitem.h"

class CChrRomItemListDisplayModel : public QAbstractListModel
{
	Q_OBJECT

public:
	CChrRomItemListDisplayModel(QObject* parent = nullptr);
	~CChrRomItemListDisplayModel() override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QList<IChrRomBankItem*> bankItems() { return chrRomBankItems; }
	void setBankItems(QList<IChrRomBankItem*> items) { chrRomBankItems = items; }

public slots:
	void update();

private:
	QList<IChrRomBankItem*> chrRomBankItems;
};

#endif // CCHRROMITEMLISTDISPLAYMODEL_H
