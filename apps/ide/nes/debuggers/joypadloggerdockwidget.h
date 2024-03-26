#ifndef JOYPADLOGGERDOCKWIDGET_H
#define JOYPADLOGGERDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "panzoomrenderer.h"

#include "debuggerupdatethread.h"

namespace Ui
{
	class JoypadLoggerDockWidget;
}

class JoypadLoggerDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit JoypadLoggerDockWidget(QWidget* parent = nullptr);
	~JoypadLoggerDockWidget() override;

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void changeEvent(QEvent* e) override;

public slots:
	void renderData();
	void updateTargetMachine(QString target);

private:
	Ui::JoypadLoggerDockWidget* ui;
	//   char* imgData;
	//   PanZoomRenderer* renderer;
	//   DebuggerUpdateThread* pThread;
};

#endif // JOYPADLOGGERDOCKWIDGET_H
