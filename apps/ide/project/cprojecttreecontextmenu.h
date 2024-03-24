#ifndef CPROJECTTREECONTEXTMENU_H
#define CPROJECTTREECONTEXTMENU_H

#include "model/iuuidvisitor.h"
#include <QPoint>
#include <QWidget>
#include <QMenu>

class CProjectModel;

class CProjectTreeContextMenu : public QObject, public IUuidVisitor
{
	Q_OBJECT

public:
	CProjectTreeContextMenu(QWidget* menuParent, QPoint pos, CProjectModel* project);

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
	QPoint m_position;
	QWidget* m_parent;
	CProjectModel* m_project;
	QUuid m_targetUuid;

	// Popup dialogs that instruct the user to do something.
	bool confirmChoice(const QString& caption, const QString& text);
	QList<QString> selectExistingFiles(const QString& caption);
	QString selectNewFileName();
	QString selectNewItemName(const QString& caption, const QString& text);

	void appendGlobalMenuItems(QMenu* menu);

private slots:
	void newGraphicsBank();
	void newPalette();
	void newSourceFile();
	void newTile();
	void newScreen();
	void newMusicFile();

	void fileProperties();

	void addBinaryFile();
	void addSourceFile();
	void addMusicFile();

	void deleteGraphicsBank();
	void deletePalette();
	void deleteTile();
	void removeBinaryFile();
	void removeSourceFile();
	void removeMusicFile();
};

#endif // CPROJECTTREECONTEXTMENU_H
