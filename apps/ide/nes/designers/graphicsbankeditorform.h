#ifndef GRAPHICSBANKEDITORFORM_H
#define GRAPHICSBANKEDITORFORM_H

#include <QList>
#include <QLabel>

#include "cdesignereditorbase.h"
#include "cchrromitemtabledisplaymodel.h"
#include "cchrrombankitemdelegate.h"
#include "ichrrombankitem.h"
#include "iprojecttreeviewitem.h"

#include "panzoomrenderer.h"
#include "tilificationthread.h"

namespace Ui
{
	class GraphicsBankEditorForm;
}

class GraphicsBankEditorForm : public CDesignerEditorBase
{
	Q_OBJECT

public:
	GraphicsBankEditorForm(uint32_t size, QList<IChrRomBankItem*> bankItems, IProjectTreeViewItem* link = 0,
	                       QWidget* parent = 0);
	~GraphicsBankEditorForm() override;
	void updateChrRomBankItemList(QList<IChrRomBankItem*> bankItems);

	// Member getters.
	QList<IChrRomBankItem*> bankItems();
	uint32_t bankSize();

protected:
	void changeEvent(QEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void updateInfoText(int x = -1, int y = -1);
	bool eventFilter(QObject* obj, QEvent* event) override;
	void renderer_enterEvent(QEvent* event);
	void renderer_leaveEvent(QEvent* event);
	void renderer_mouseMoveEvent(QMouseEvent* event);
	void updateUi();

private:
	Ui::GraphicsBankEditorForm* ui;
	QLabel* info;
	CChrRomItemTableDisplayModel* model;
	PanZoomRenderer* renderer;
	CChrRomBankItemDelegate* delegate;
	int8_t* imgData;
	TilificationThread* pThread;
	QByteArray tilifiedData;

private slots:
	void renderData();
	void renderData(QByteArray output);
	void updateList();
	void snapTo(QString item) override;
	void applyChangesToTab(QString uuid) override;
	void itemRemoved(QUuid uuid) override;
	void applyProjectPropertiesToTab() override;

	void updateTargetMachine(QString target)
	{
	}

	void on_moveUp_clicked();

	void on_moveDown_clicked();

	void on_bankSize_currentIndexChanged(int index);
	void tableView_doubleClicked(QModelIndex index);

signals:
	void prepareToTilify();
	void addToTilificator(IChrRomBankItem* item);
	void tilify();
};

#endif // GRAPHICSBANKEDITORFORM_H
