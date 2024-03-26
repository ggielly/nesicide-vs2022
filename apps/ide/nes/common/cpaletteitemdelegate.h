#ifndef CPALETTEITEMDELEGATE_H
#define CPALETTEITEMDELEGATE_H

#include <QItemDelegate>

class CPaletteItemDelegate : public QItemDelegate
{
public:
	CPaletteItemDelegate(QObject* pParent = nullptr) : QItemDelegate(pParent)
	{
	}

	void paint(QPainter* pPainter, const QStyleOptionViewItem& rOption, const QModelIndex& rIndex) const override
	{
		QStyleOptionViewItem ViewOption(rOption);

		ViewOption.palette.setColor(QPalette::Highlight, rIndex.data(Qt::BackgroundColorRole).value<QColor>());
		ViewOption.palette.setColor(QPalette::HighlightedText, rIndex.data(Qt::ForegroundRole).value<QColor>());

		if (rOption.state == QStyle::State_Selected)
		{
			ViewOption.font.setBold(true);
		}

		QItemDelegate::paint(pPainter, ViewOption, rIndex);
	}
};

#endif // CPALETTEITEMDELEGATE_H
