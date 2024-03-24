#ifndef CODEDATALOGGERDOCKWIDGET_H
#define CODEDATALOGGERDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "panzoomrenderer.h"

#include "debuggerupdatethread.h"

enum
{
	CodeDataLogger_CPU,
	CodeDataLogger_PPU,
	CodeDataLogger_PRGROM // Not done yet.
};

namespace Ui
{
	class CodeDataLoggerDockWidget;
}

class CodeDataLoggerDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit CodeDataLoggerDockWidget(QWidget* parent = 0);
	~CodeDataLoggerDockWidget() override;

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void changeEvent(QEvent* e) override;
	void updateInfoText(int x = -1, int y = -1);
	bool eventFilter(QObject* obj, QEvent* event) override;
	void renderer_enterEvent(QEvent* event);
	void renderer_leaveEvent(QEvent* event);
	void renderer_mouseMoveEvent(QMouseEvent* event);

private:
	Ui::CodeDataLoggerDockWidget* ui;
	PanZoomRenderer* renderer;
	DebuggerUpdateThread* pThread;

public slots:
	void renderData();
	void updateTargetMachine(QString target);

private slots:
	void on_exportData_clicked();
	void on_displaySelect_currentIndexChanged(int index);
};

#endif // CODEDATALOGGERDOCKWIDGET_H
