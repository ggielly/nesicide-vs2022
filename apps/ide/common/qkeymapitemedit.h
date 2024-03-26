#ifndef QKEYMAPITEMEDIT_H
#define QKEYMAPITEMEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class QKeymapItemEdit : public QLineEdit
{
	Q_OBJECT

public:
	explicit QKeymapItemEdit(QWidget* parent = nullptr);

protected:
	bool event(QEvent*) override;

	void contextMenuEvent(QContextMenuEvent*) override
	{
	}

signals:

public slots:
};

#endif // QKEYMAPITEMEDIT_H
