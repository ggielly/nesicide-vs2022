#ifndef CBREAKPOINTDISPLAYMODEL_H
#define CBREAKPOINTDISPLAYMODEL_H

#include <QAbstractTableModel>

#include "cbreakpointinfo.h"

class CBreakpointDisplayModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CBreakpointDisplayModel(CBreakpointInfo* pBreakpoints, QObject* parent = nullptr);
	~CBreakpointDisplayModel() override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private:
	CBreakpointInfo* m_pBreakpoints;
	char* m_modelStringBuffer;

public slots:
	void update();
};

#endif // CBREAKPOINTDISPLAYMODEL_H
