#ifndef CEXPANDABLESTATUSBAR_H
#define CEXPANDABLESTATUSBAR_H

#include <QFrame>

namespace Ui
{
	class CExpandableStatusBar;
}

class CExpandableStatusBar : public QFrame
{
	Q_OBJECT

public:
	explicit CExpandableStatusBar(QWidget* parent = nullptr);

	void addPermanentWidget(QWidget* widget, int stretch = 0);
	void addExpandingWidget(QWidget* widget, int stretch = 0);
	void addWidget(QWidget* widget, int stretch = 0);
	void removeWidget(QWidget* widget);
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	Ui::CExpandableStatusBar* ui;
	QWidget* expandableWidget;
	QPoint touchPos;

signals:

public slots:

protected:
private slots:
	void on_splitter_splitterMoved(int pos, int index);
};

#endif // CEXPANDABLESTATUSBAR_H
