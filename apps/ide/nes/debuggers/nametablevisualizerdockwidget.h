#ifndef NAMETABLEVISUALIZERDOCKWIDGET_H
#define NAMETABLEVISUALIZERDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "panzoomrenderer.h"

#include "debuggerupdatethread.h"

namespace Ui
{
	class NameTableVisualizerDockWidget;
}

class NameTableVisualizerDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit NameTableVisualizerDockWidget(QWidget* parent = nullptr);
	~NameTableVisualizerDockWidget() override;

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void changeEvent(QEvent* e) override;
	void updateInfoText(int x = -1, int y = -1);
	bool eventFilter(QObject* obj, QEvent* event) override;
	void renderer_enterEvent(QEvent* event);
	void renderer_leaveEvent(QEvent* event);
	void renderer_mouseMoveEvent(QMouseEvent* event);

public slots:
	void renderData();
	void updateTargetMachine(QString target) const;

private slots:
	void on_showVisible_toggled(bool checked);

private:
	Ui::NameTableVisualizerDockWidget* ui;
	PanZoomRenderer* renderer;
	DebuggerUpdateThread* pThread;
};

#endif // NAMETABLEVISUALIZERDOCKWIDGET_H
