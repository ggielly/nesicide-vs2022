#ifndef STARTUPSPLASHDIALOG_H
#define STARTUPSPLASHDIALOG_H

#include <QDialog>

namespace Ui
{
	class StartupSplashDialog;
}

class StartupSplashDialog : public QDialog
{
	Q_OBJECT

public:
	explicit StartupSplashDialog(QWidget* parent = 0);
	~StartupSplashDialog() override;

private:
	Ui::StartupSplashDialog* ui;
};

#endif // STARTUPSPLASHDIALOG_H
