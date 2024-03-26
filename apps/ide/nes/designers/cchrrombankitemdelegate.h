#ifndef CCHRROMBANKITEMDELEGATE_H
#define CCHRROMBANKITEMDELEGATE_H

#include <QStyledItemDelegate>

class CChrRomBankItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit CChrRomBankItemDelegate(QObject* parent = nullptr);

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	                      const QModelIndex& index) const override;

	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model,
	                  const QModelIndex& index) const override;
	void updateEditorGeometry(QWidget* editor,
	                          const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // CCHRROMBANKITEMDELEGATE_H
