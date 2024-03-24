#ifndef QSCIAPISCA65_H
#define QSCIAPISCA65_H

#include <Qsci/qsciscintilla.h>
#include <Qsci/qsciapis.h>
#include <QObject>

class QsciAPIsCA65 : public QsciAPIs
{
public:
	QsciAPIsCA65(QsciLexer* lexer);
	~QsciAPIsCA65() override;

	//! \reimp
	void updateAutoCompletionList(const QStringList& context,
	                              QStringList& list) override;

	//! \reimp
	void autoCompletionSelected(const QString& sel) override;

	//! \reimp
	QStringList callTips(const QStringList& context, int commas,
	                     QsciScintilla::CallTipsStyle style, QList<int>& shifts) override;
};

#endif // QSCIAPISCA65_H
