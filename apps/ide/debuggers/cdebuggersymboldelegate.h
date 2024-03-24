#ifndef CDEBUGGERSYMBOLDELEGATE_H
#define CDEBUGGERSYMBOLDELEGATE_H

#include <QStyledItemDelegate>

class CDebuggerSymbolDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit CDebuggerSymbolDelegate(QObject* parent = 0);

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	                      const QModelIndex& index) const override;

	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model,
	                  const QModelIndex& index) const override;
	void updateEditorGeometry(QWidget* editor,
	                          const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // CDEBUGGERSYMBOLDELEGATE_H
