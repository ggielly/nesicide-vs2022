#ifndef APPEVENTFILTER_H
#define APPEVENTFILTER_H

#include <QObject>
#include <QEvent>

class AppEventFilter : public QObject
{
	Q_OBJECT

public:
	explicit AppEventFilter(QObject* parent = nullptr);

	bool eventFilter(QObject* obj, QEvent* event) override;

signals:
	void applicationActivationChanged(bool activated);

public slots:


private:
	bool inActivationEvent;
};

#endif // APPEVENTFILTER_H
