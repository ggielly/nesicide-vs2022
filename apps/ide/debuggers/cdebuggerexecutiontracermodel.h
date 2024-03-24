#ifndef CDEBUGGEREXECUTIONTRACERMODEL_H
#define CDEBUGGEREXECUTIONTRACERMODEL_H

#include <QAbstractTableModel>
#include "ctracer.h"

class CDebuggerExecutionTracerModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CDebuggerExecutionTracerModel(QObject* parent);
	~CDebuggerExecutionTracerModel() override;
	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column,
	                  const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	void showCPU(bool show);
	void showPPU(bool show);

public slots:
	void update();

private:
	CTracer* m_pTracer;
	bool m_bShowCPU;
	bool m_bShowPPU;
	char* m_modelStringBuffer;
};

#endif // CDEBUGGEREXECUTIONTRACERMODEL_H
