#ifndef CDEBUGGERNUMERICITEMDELEGATE_H
#define CDEBUGGERNUMERICITEMDELEGATE_H

#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QLineEdit>

class CDebuggerNumericItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit CDebuggerNumericItemDelegate(QObject* parent = 0);

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	                      const QModelIndex& index) const override;

	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model,
	                  const QModelIndex& index) const override;
	void updateEditorGeometry(QWidget* editor,
	                          const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // CDEBUGGERNUMERICITEMDELEGATE_H
