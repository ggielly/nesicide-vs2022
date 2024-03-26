#ifndef MAPPERINFORMATIONDOCKWIDGET_H
#define MAPPERINFORMATIONDOCKWIDGET_H

#include <QMap>

#include "cdebuggerbase.h"

namespace Ui
{
	class MapperInformationDockWidget;
}

class MapperInformationDockWidget : public CDebuggerBase
{
	Q_OBJECT

public:
	explicit MapperInformationDockWidget(QWidget* parent = nullptr);
	~MapperInformationDockWidget() override;

protected:
	void showEvent(QShowEvent* e) override;
	void hideEvent(QHideEvent* e) override;
	void changeEvent(QEvent* e) override;

public slots:
	void updateInformation();
	void machineReady();
	void updateTargetMachine(QString target);

private:
	Ui::MapperInformationDockWidget* ui;
	QMap<int, QWidget*> internalPageMap;
};

#endif // MAPPERINFORMATIONDOCKWIDGET_H
