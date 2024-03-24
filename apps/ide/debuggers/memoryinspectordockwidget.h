#ifndef MEMORYINSPECTORDOCKWIDGET_H
#define MEMORYINSPECTORDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "cdebuggermemorydisplaymodel.h"
#include "cdebuggernumericitemdelegate.h"
#include "cmemorydata.h"

#include "cbreakpointinfo.h"

#include "qhexedit.h"

namespace Ui
{
	class MemoryInspectorDockWidget;
}

class MemoryInspectorDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit MemoryInspectorDockWidget(memDBFunc memDB, CBreakpointInfo* pBreakpoints, QWidget* parent = 0);
	~MemoryInspectorDockWidget() override;

protected:
	void showEvent(QShowEvent* e) override;
	void hideEvent(QHideEvent* e) override;
	void contextMenuEvent(QContextMenuEvent* e) override;
	void changeEvent(QEvent* e) override;

public slots:
	void updateMemory();
	void updateTargetMachine(QString target);
	void snapToHandler(QString item);
	void applyEnvironmentSettings();

signals:
	void breakpointsChanged();

private:
	Ui::MemoryInspectorDockWidget* ui;
	CDebuggerMemoryDisplayModel* model;
	CDebuggerNumericItemDelegate* delegate;
	CBreakpointInfo* m_pBreakpoints;
	memDBFunc m_memDBFunc;
	CMemoryDatabase* m_memDB;
	QHexEdit* m_editor;
	QByteArray m_snapshot;

private slots:
	void on_actionBreak_on_CPU_write_here_triggered();
	void on_actionBreak_on_CPU_read_here_triggered();
	void on_actionBreak_on_CPU_access_here_triggered();
};

#endif // MEMORYINSPECTORDOCKWIDGET_H
