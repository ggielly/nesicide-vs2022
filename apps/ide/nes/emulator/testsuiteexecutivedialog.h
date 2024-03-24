#ifndef TESTSUITEEXECUTIVEDIALOG_H
#define TESTSUITEEXECUTIVEDIALOG_H

#include <QDialog>

#include "stdint.h"

class MainWindow;

namespace Ui
{
	class TestSuiteExecutiveDialog;
}

class TestSuiteExecutiveDialog : public QDialog
{
	Q_OBJECT

public:
	explicit TestSuiteExecutiveDialog(QWidget* parent = 0);
	~TestSuiteExecutiveDialog() override;

protected:
	void showEvent(QShowEvent*) override;
	void hideEvent(QHideEvent*) override;
	void closeEvent(QCloseEvent*) override;

private:
	Ui::TestSuiteExecutiveDialog* ui;
	bool aborted;
	int testStart;
	int testEnd;
	int testRunning;
	int testPhase;
	int testsPassed;
	void loadTestSuite(QString testSuiteFileName);
	void executeTests(int start, int end);
	void doTestPhase();

signals:
	void openNesROM(QString romFile, bool runRom);
	void startEmulation();
	void pauseEmulationAfter(int32_t frames);

private slots:
	void on_save_clicked();
	void on_clearAll_clicked();
	void on_load_clicked();
	void on_execute_clicked();
	void on_executeSelection_clicked();
	void on_abort_clicked();
	void updateProgress();
	void updateTargetMachine(QString target);
	void machineReady();
	void emulatorPausedAfter();
	void on_clear_clicked();
};

#endif // TESTSUITEEXECUTIVEDIALOG_H
