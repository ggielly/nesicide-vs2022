#ifndef CPROJECTTREEOPENACTION_H
#define CPROJECTTREEOPENACTION_H

#include "model/iuuidvisitor.h"
#include <QObject>
#include <QTreeWidget>

class CProjectModel;
class CSubModel;
class CProjectTabWidget;

class CProjectTreeOpenAction : public QObject, public IUuidVisitor
{
	Q_OBJECT

public:
	CProjectTreeOpenAction(CProjectTabWidget* tabWidget, CProjectModel* project);

	void visit(CUuid&) override;
	void visit(CAttributeUuid&) override;
	void visit(CBinaryFileUuid&) override;
	void visit(CFilterUuid&) override;
	void visit(CGraphicsBankUuid&) override;
	void visit(CSourceFileUuid&) override;
	void visit(CTileStampUuid&) override;
	void visit(CMusicFileUuid&) override;

	void visit(CChrRomUuid&) override;
	void visit(CPrgRomUuid&) override;

private:
	CProjectTabWidget* m_tabWidget;
	CProjectModel* m_project;

	void doVisit(CSubModel* model, const QUuid& uuid);
};

#endif // CPROJECTTREEOPENACTION_H
