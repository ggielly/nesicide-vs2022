#ifndef APUINFORMATIONDOCKWIDGET_H
#define APUINFORMATIONDOCKWIDGET_H

#include "cdebuggerbase.h"

namespace Ui
{
	class APUInformationDockWidget;
}

class APUInformationDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit APUInformationDockWidget(QWidget* parent = nullptr);
	~APUInformationDockWidget() override;

protected:
	void showEvent(QShowEvent* e) override;
	void hideEvent(QHideEvent* e) override;
	void changeEvent(QEvent* e) override;

public slots:
	void updateInformation();
	void updateTargetMachine(QString target);

private:
	Ui::APUInformationDockWidget* ui;
};

#endif // APUINFORMATIONDOCKWIDGET_H
