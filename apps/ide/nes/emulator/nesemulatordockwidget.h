#ifndef NESEMULATORDOCKWIDGET_H
#define NESEMULATORDOCKWIDGET_H

#include "nes_emulator_core.h"
#include "nesemulatorrenderer.h"

#include <QDockWidget>
#include <QKeyEvent>

namespace Ui
{
	class NESEmulatorDockWidget;
}

class NESEmulatorDockWidget : public QDockWidget
{
	Q_OBJECT

public:
	explicit NESEmulatorDockWidget(QWidget* parent = nullptr);
	~NESEmulatorDockWidget() override;

	void setLinearInterpolation(bool enabled) const { renderer->setLinearInterpolation(enabled); }
	void set43Aspect(bool enabled) { renderer->set43Aspect(enabled); }
	void setScalingFactor(float factor);

protected:
	void changeEvent(QEvent* e) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

signals:
	void controllerInput(uint32_t* joy);

private:
	Ui::NESEmulatorDockWidget* ui;
	CNESEmulatorRenderer* renderer;
	char* imgData;
	uint32_t m_joy[NUM_CONTROLLERS];
	QRect ncRect;

private slots:
	void renderData();
	void updateTargetMachine(QString target) const;
};

#endif // NESEMULATORDOCKWIDGET_H
