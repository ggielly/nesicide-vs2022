#ifndef QSCILEXERCA65_H
#define QSCILEXERCA65_H

#include <qobject.h>

#include "Qsci/qsciglobal.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercustom.h"

class QsciLexerCA65 : public QsciLexerCustom
{
	Q_OBJECT

public:
	// Styles
	enum
	{
		CA65_Default,
		CA65_Opcode,
		CA65_Label,
		CA65_Keyword,
		CA65_QuotedString,
		CA65_Comment,
		CA65_Number
	};

	QsciLexerCA65(QObject* parent = nullptr);
	~QsciLexerCA65() override;

	const char* language() const override { return "CA65"; }
	QString description(int style) const override;
	void styleText(int start, int end) override;

	const char* blockEnd(int* style = nullptr) const override;
	const char* blockStart(int* style = nullptr) const override;
	const char* blockStartKeyword(int* style = nullptr) const override;

	bool eolFill(int /*style*/) const override { return true; }

	virtual QColor defaultColor() const;
	QColor defaultColor(int style) const override;

	virtual QColor defaultPaper() const;
	QColor defaultPaper(int style) const override;
	QColor paper(int style) const override;

	virtual QFont defaultFont() const;
	QFont defaultFont(int style) const override;

	const char* wordCharacters() const override;

	int styleBitsNeeded() const override { return 8; }

	bool readSettings(QSettings& qs, const char* prefix = "/Scintilla");
	bool writeSettings(QSettings& qs, const char* prefix = "/Scintilla");

protected:
	bool readProperties(QSettings& qs, const QString& prefix) override;
	bool writeProperties(QSettings& qs, const QString& prefix) const override;

protected:
	QRegExp opcodeRegex;
	QRegExp keywordRegex;
	QRegExp labelRegex;
	QRegExp numberRegex;
};

#endif // QSCILEXERCA65_H
