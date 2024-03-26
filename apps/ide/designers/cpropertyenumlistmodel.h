#ifndef CPROPERTYENUMLISTMODEL_H
#define CPROPERTYENUMLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "cpropertyitem.h"

enum
{
	PropertyEnumCol_Default = 0,
	PropertyEnumCol_Symbol,
	PropertyEnumCol_Value,
	PropertyEnumCol_MAX
};

class CPropertyEnumListModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit CPropertyEnumListModel(bool editable, QObject* parent = nullptr);
	~CPropertyEnumListModel() override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	void removeRow(int row, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	void insertRow(QString text, const QModelIndex& parent = QModelIndex());

	QString getItems();
	void setItems(QString itemsStr);

public slots:
	void update();

private:
	QList<PropertyEnumItem> m_items;
	bool m_editable;
};

#endif // CPROPERTYENUMLISTMODEL_H
