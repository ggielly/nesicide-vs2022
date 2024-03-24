#ifndef BREAKPOINTDOCKWIDGET_H
#define BREAKPOINTDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "cregisterdata.h"
#include "cbreakpointinfo.h"
#include "cbreakpointdisplaymodel.h"

#include "ixmlserializable.h"

namespace Ui
{
	class BreakpointDockWidget;
}

class BreakpointDockWidget : public CDebuggerBase, public IXMLSerializable
{
	Q_OBJECT

public:
	BreakpointDockWidget(CBreakpointInfo* pBreakpoints, QWidget* parent = 0);
	~BreakpointDockWidget() override;

	// IXMLSerializable interface
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

protected:
	void changeEvent(QEvent* e) override;
	void showEvent(QShowEvent* e) override;
	void contextMenuEvent(QContextMenuEvent* e) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

signals:
	void breakpointsChanged();

private:
	Ui::BreakpointDockWidget* ui;
	CBreakpointInfo* m_pBreakpoints;
	CBreakpointDisplayModel* model;
	bool eventFilter(QObject* obj, QEvent* event) override;

public slots:
	void updateData();
	void updateTargetMachine(QString target);

private slots:
	void on_tableView_pressed(QModelIndex index);
	void on_tableView_doubleClicked(QModelIndex index);
	void on_actionDisable_All_Breakpoints_triggered();
	void on_actionEnable_All_Breakpoints_triggered();
	void on_actionDisable_Breakpoint_triggered();
	void on_actionEnable_Breakpoint_triggered();
	void on_actionEdit_Breakpoint_triggered();
	void on_actionRemove_Breakpoint_triggered();
	void on_actionRemove_All_Breakpoints_triggered();
	void on_actionAdd_Breakpoint_triggered();
};

#endif // BREAKPOINTDOCKWIDGET_H
