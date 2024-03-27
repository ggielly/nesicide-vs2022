#ifndef BREAKPOINTWATCHERTHREAD_H
#define BREAKPOINTWATCHERTHREAD_H

#include <QThread>
#include <QSemaphore>

class BreakpointWatcherWorker : public QObject
{
	Q_OBJECT

public:
	BreakpointWatcherWorker(QObject* parent = nullptr);
	~BreakpointWatcherWorker() override;

	void breakpoint();

signals:
	void breakpointHit();
	void showPane(int pane);
};

class BreakpointWatcherThread : public QObject
{
	Q_OBJECT

public:
	BreakpointWatcherThread(QObject* parent = nullptr);
	~BreakpointWatcherThread() override;

signals:
	void breakpointHit();
	void showPane(int pane);

public slots:
	void breakpoint() const { pWorker->breakpoint(); }

protected:
	BreakpointWatcherWorker* pWorker;
	QThread* pThread;
};

#endif // BREAKPOINTWATCHERTHREAD_H
