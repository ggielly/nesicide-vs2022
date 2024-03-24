#ifndef CDEBUGGERREGISTERDISPLAYMODEL_H
#define CDEBUGGERREGISTERDISPLAYMODEL_H

#include <QAbstractTableModel>

#include "cregisterdata.h"

class CDebuggerRegisterDisplayModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CDebuggerRegisterDisplayModel(regDBFunc regDB, QObject* parent = 0);
	~CDebuggerRegisterDisplayModel() override;
	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int) override;
	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column,
	                  const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	int memoryType() const;
	int memoryBottom() const;
	bool memoryContains(uint32_t addr) const;

public slots:
	void update(void);

private:
	regDBFunc m_regDBFunc;
	CRegisterDatabase* m_regDB;
	char* m_modelStringBuffer;
};

#endif // CDEBUGGERREGISTERDISPLAYMODEL_H
