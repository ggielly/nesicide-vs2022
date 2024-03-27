#ifndef PPUINFORMATIONDOCKWIDGET_H
#define PPUINFORMATIONDOCKWIDGET_H

#include "cdebuggerbase.h"

namespace Ui
{
	class PPUInformationDockWidget;
}

class PPUInformationDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit PPUInformationDockWidget(QWidget* parent = nullptr);
	~PPUInformationDockWidget() override;

protected:
	void showEvent(QShowEvent* e) override;
	void hideEvent(QHideEvent* e) override;
	void changeEvent(QEvent* e) override;

public slots:
	void updateInformation();
	void updateTargetMachine(QString target) const;

private:
	Ui::PPUInformationDockWidget* ui;
};

#endif // PPUINFORMATIONDOCKWIDGET_H
