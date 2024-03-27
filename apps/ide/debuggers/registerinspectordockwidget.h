#ifndef REGISTERINSPECTORDOCKWIDGET_H
#define REGISTERINSPECTORDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "cdebuggerregisterdisplaymodel.h"
#include "cdebuggerbitfielddisplaymodel.h"
#include "cdebuggerbitfieldcomboboxdelegate.h"
#include "cdebuggernumericitemdelegate.h"
#include "cregisterdata.h"
#include "cbreakpointinfo.h"

namespace Ui
{
	class RegisterInspectorDockWidget;
}

class RegisterInspectorDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	RegisterInspectorDockWidget(regDBFunc regDB, CBreakpointInfo* pBreakpoints, QWidget* parent = nullptr);
	~RegisterInspectorDockWidget() override;

protected:
	void changeEvent(QEvent* e) override;
	void contextMenuEvent(QContextMenuEvent* e) override;
	void showEvent(QShowEvent* e) override;
	void hideEvent(QHideEvent* e) override;

public slots:
	void updateMemory();

private:
	Ui::RegisterInspectorDockWidget* ui;
	CDebuggerRegisterDisplayModel* binaryModel;
	CDebuggerBitfieldDisplayModel* bitfieldModel;
	CDebuggerBitfieldComboBoxDelegate* bitfieldDelegate;
	CDebuggerNumericItemDelegate* binaryDelegate;
	CBreakpointInfo* m_pBreakpoints;
	regDBFunc m_regDBFunc;
	CRegisterDatabase* m_regDB;
	int m_register;

private slots:
	void on_binaryView_entered(const QModelIndex& index);
	void on_binaryView_activated(const QModelIndex& index);
	void on_binaryView_pressed(const QModelIndex& index);
	void on_binaryView_clicked(const QModelIndex& index);
	void on_binaryView_doubleClicked(const QModelIndex& index);
	void on_bitfieldView_doubleClicked(const QModelIndex& index) const;
	void on_bitfieldView_clicked(const QModelIndex& index);
	void binaryView_currentChanged(const QModelIndex& index, QModelIndex);
	void updateTargetMachine(const QString& target) const;
};

#endif // REGISTERINSPECTORDOCKWIDGET_H
