#ifndef MUSICEDITORFORM_H
#define MUSICEDITORFORM_H

#include "cdesignereditorbase.h"
#include "cdesignercommon.h"

#include "Source/MainFrm.h"

#include <QWidget>
#include <QToolBar>

namespace Ui
{
	class MusicEditorForm;
}

class music_editor_form : public CDesignerEditorBase
{
	Q_OBJECT

public:
	// This takes place of the constructor and provides a singleton instance.
	static music_editor_form* instance();
	QString fileName() { return m_fileName; }
	void setFileName(const QString& file_name) { m_fileName = file_name; }
	void setTreeLink(IProjectTreeViewItem* link) { InitTabItem(link); }
	bool exportData();
	~music_editor_form() override;

	// ICenterWidgetItem Interface Implmentation
	void onSave() override;
	void onClose() override;
	QMessageBox::StandardButton onCloseQuery() override;

private:
	music_editor_form(const QString& file_name, const QByteArray& music_data, IProjectTreeViewItem* link = nullptr, QWidget* parent = nullptr);
	Ui::MusicEditorForm* ui_;
	QString m_fileName;
	static music_editor_form* instance_;

public slots:
	static void updateTargetMachine(QString /*target*/)
	{
	}

	void editor_modification_changed(bool m);
	void document_saved();
	void document_closed();
};

#endif // MUSICEDITORFORM_H
