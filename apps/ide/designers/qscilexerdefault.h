#ifndef QSCILEXERDEFAULT_H
#define QSCILEXERDEFAULT_H

#include <qobject.h>

#include "Qsci/qsciglobal.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercustom.h"

class QsciLexerDefault : public QsciLexerCustom
{
	Q_OBJECT

public:
	// Styles
	enum
	{
		Default_Default
	};

	QsciLexerDefault(QObject* parent = nullptr);
	~QsciLexerDefault() override;

	const char* language() const override { return "Default"; }
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

	const char* wordCharacters() const override;

	int styleBitsNeeded() const override { return 8; }

	bool readSettings(QSettings& qs, const char* prefix = "/Scintilla");
	bool writeSettings(QSettings& qs, const char* prefix = "/Scintilla");

protected:
	bool readProperties(QSettings& qs, const QString& prefix) override;
	bool writeProperties(QSettings& qs, const QString& prefix) const override;
};

#endif // QSCILEXERDEFAULT_H
