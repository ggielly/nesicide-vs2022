#ifndef EXECUTIONVISUALIZERDOCKWIDGET_H
#define EXECUTIONVISUALIZERDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "panzoomrenderer.h"

#include "cexecutionmarkerdisplaymodel.h"

#include "debuggerupdatethread.h"

#include "ixmlserializable.h"

namespace Ui
{
	class ExecutionVisualizerDockWidget;
}

class ExecutionVisualizerDockWidget : public CDebuggerBase, public IXMLSerializable
{
	Q_OBJECT

public:
	explicit ExecutionVisualizerDockWidget(QWidget* parent = nullptr);
	~ExecutionVisualizerDockWidget() override;

	// IXMLSerializable interface
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void changeEvent(QEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;

public slots:
	void renderData();
	void updateTargetMachine(QString target);

private slots:
	void on_actionRemove_Marker_triggered();
	void on_actionReset_Marker_Data_triggered();
	void tableView_currentChanged(QModelIndex index, QModelIndex);

signals:
	void breakpointsChanged();

private:
	Ui::ExecutionVisualizerDockWidget* ui;
	CExecutionMarkerDisplayModel* model;
	PanZoomRenderer* renderer;
	DebuggerUpdateThread* pThread;
};

#endif // EXECUTIONVISUALIZERDOCKWIDGET_H
