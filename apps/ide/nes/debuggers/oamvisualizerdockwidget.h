#ifndef OAMVISUALIZERDOCKWIDGET_H
#define OAMVISUALIZERDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "panzoomrenderer.h"

#include "debuggerupdatethread.h"

namespace Ui
{
	class OAMVisualizerDockWidget;
}

class OAMVisualizerDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit OAMVisualizerDockWidget(QWidget* parent = 0);
	~OAMVisualizerDockWidget() override;

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void changeEvent(QEvent* e) override;

public slots:
	void renderData();
	void updateTargetMachine(QString target);

private slots:
	void on_showVisible_toggled(bool checked);
	void on_updateScanline_editingFinished();

private:
	Ui::OAMVisualizerDockWidget* ui;
	PanZoomRenderer* renderer;
	DebuggerUpdateThread* pThread;
};

#endif // OAMVISUALIZERDOCKWIDGET_H
