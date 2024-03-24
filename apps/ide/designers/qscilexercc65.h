#ifndef QSCILEXERCC65_H
#define QSCILEXERCC65_H

#include <qobject.h>

#include "Qsci/qsciglobal.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercpp.h"

class QsciLexerCC65 : public QsciLexerCPP
{
	Q_OBJECT

public:
	QsciLexerCC65(QObject* parent = 0);
	~QsciLexerCC65() override;

	virtual QFont defaultFont() const;
	QFont defaultFont(int style) const override;

	QFont font(int style) const override;
};

#endif // QSCILEXERCC65_H
