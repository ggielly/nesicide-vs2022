#ifndef QSCILEXERBIN_H
#define QSCILEXERBIN_H

#include <qobject.h>

#include "Qsci/qsciglobal.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercustom.h"

class QsciLexerBin : public QsciLexerCustom
{
	Q_OBJECT

public:
	// Styles
	enum
	{
		Bin_Default
	};

	QsciLexerBin(QObject* parent = 0);
	~QsciLexerBin() override;

	const char* language() const override { return "Bin"; }
	QString description(int style) const override;

	void styleText(int start, int end) override;

	bool eolFill(int /*style*/) const override { return true; }

	virtual QColor defaultColor() const;
	QColor defaultColor(int style) const override;

	virtual QColor defaultPaper() const;
	QColor defaultPaper(int style) const override;
	QColor paper(int style) const override;

	virtual QFont defaultFont() const;
	QFont defaultFont(int style) const override;

	int styleBitsNeeded() const override { return 1; }
};

#endif // QSCILEXERBIN_H
