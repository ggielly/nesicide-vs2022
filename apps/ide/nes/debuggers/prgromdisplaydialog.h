#ifndef PRGROMDISPLAYDIALOG_H
#define PRGROMDISPLAYDIALOG_H

#include "cdesignereditorbase.h"
#include "iprojecttreeviewitem.h"

#include "stdint.h"

#include <qhexedit.h>

namespace Ui
{
	class PRGROMDisplayDialog;
}

class PRGROMDisplayDialog : public CDesignerEditorBase
{
	Q_OBJECT

public:
	PRGROMDisplayDialog(uint8_t* bankData, IProjectTreeViewItem* link = 0, QWidget* parent = 0);
	~PRGROMDisplayDialog() override;

	void setRomData(unsigned char* data)
	{
		m_data = data;
	}

protected:
	void changeEvent(QEvent* e) override;
	void showEvent(QShowEvent* e) override;

protected:
	unsigned char* m_data;

private:
	Ui::PRGROMDisplayDialog* ui;
	QHexEdit* m_editor;

private slots:
	void applyEnvironmentSettingsToTab() override;

	void updateTargetMachine(QString /*target*/)
	{
	}
};

#endif // PRGROMDISPLAYDIALOG_H
