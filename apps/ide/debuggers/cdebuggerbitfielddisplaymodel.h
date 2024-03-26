#ifndef CDEBUGGERBITFIELDDISPLAYMODEL_H
#define CDEBUGGERBITFIELDDISPLAYMODEL_H

#include <QAbstractItemModel>

#include "cregisterdata.h"

class CDebuggerBitfieldDisplayModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CDebuggerBitfieldDisplayModel(regDBFunc regDB, QObject* parent = nullptr);
	~CDebuggerBitfieldDisplayModel() override;
	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column,
	                  const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	void setRegister(int newRegister)
	{
		m_register = newRegister;
	}

public slots:
	void update(void);

private:
	regDBFunc m_regDB;
	int m_register;
	char* m_modelStringBuffer;
};

#endif // CDEBUGGERBITFIELDDISPLAYMODEL_H
