#include "musiceditorform.h"
#include "ui_musiceditorform.h"

#include "cqtmfc_famitracker.h"

#include "cqtmfc.h"

#include "cnesicideproject.h"

#include "Source/FamiTrackerDoc.h"
#include "Source/TextExporter.h"

#include <QDir>



music_editor_form* music_editor_form::instance_ = nullptr;

music_editor_form* music_editor_form::instance()
{
	if (!instance_)
	{
		instance_ = new music_editor_form(QString(), QByteArray());
	}

	return instance_;
}

music_editor_form::music_editor_form([[maybe_unused]] const QString& file_name, [[maybe_unused]] const QByteArray&
                                     music_data, IProjectTreeViewItem* link, QWidget* parent) :
	CDesignerEditorBase(link, parent),
	ui_(new Ui::MusicEditorForm)
{
	ui_->setupUi(this);

	// Initialize FamiTracker...
	ideifyFamiTracker();
	qtMfcInit(this);
	AfxGetApp()->InitInstance();

	const auto pMainFrame = static_cast<CMainFrame*>(AfxGetMainWnd());
	setCentralWidget(pMainFrame->toQWidget());
	pMainFrame->toQWidget()->setAcceptDrops(true);

	connect(AfxGetApp()->m_pMainWnd,SIGNAL(addToolBarWidget(QToolBar*)), this,
	        SIGNAL(addToolBarWidget(QToolBar*)));
	connect(AfxGetApp()->m_pMainWnd,SIGNAL(removeToolBarWidget(QToolBar*)), this,
	        SIGNAL(removeToolBarWidget(QToolBar*)));
	connect(AfxGetApp()->m_pMainWnd,SIGNAL(editor_modificationChanged(bool)), this,
	        SLOT(editor_modificationChanged(bool)));
}

music_editor_form::~music_editor_form()
{
	// Close FamiTracker.
	AfxGetMainWnd()->OnClose();
	AfxGetApp()->ExitInstance();

	delete ui_;
}

void music_editor_form::editor_modification_changed(bool m)
{
	setModified(m);

	emit editor_modified(m);
}

void music_editor_form::document_saved()
{
}

void music_editor_form::document_closed()
{
	//   QSettings settings(QSettings::IniFormat, QSettings::UserScope, "CSPSoftware", "FamiTracker");

	//   settings.setValue("FamiTrackerWindowGeometry",saveGeometry());
	//   settings.setValue("FamiTrackerWindowState",saveState());

	//   // TODO: Handle unsaved documents or other pre-close stuffs
	//   theApp.ExitInstance();

	//   exit(0);
}

void music_editor_form::onSave()
{
	CDesignerEditorBase::onSave();

	AfxGetMainWnd()->SendMessage(ID_FILE_SAVE);

	setModified(false);
}

void music_editor_form::onClose()
{
	openFile(nullptr);
}

QMessageBox::StandardButton music_editor_form::onCloseQuery()
{
	QMessageBox::StandardButton doSave;

	doSave = CDesignerEditorBase::onCloseQuery();
	if (doSave == QMessageBox::No)
	{
		// Need to nix the MFC modified flag.
		auto pDoc = static_cast<CFamiTrackerDoc*>(AfxGetMainWnd()->GetActiveDocument());

		pDoc->SetModifiedFlag(FALSE);
	}

	return doSave;
}

bool music_editor_form::exportData()
{
	//   AfxGetMainWnd()->SendMessage(ID_FILE_EXPORTTEXT);
	auto pDoc = static_cast<CFamiTrackerDoc*>(AfxGetMainWnd()->GetActiveDocument());
	QDir exportDir(CNesicideProject::instance()->getProjectOutputBasePath());
	auto fileName = QString(pDoc->GetFileTitle().GetBuffer());
	fileName += ".ftxt";
	CString FileName(exportDir.absoluteFilePath(fileName));

	CTextExport Exporter;
	CString sResult = Exporter.ExportFile(FileName, pDoc);
	if (sResult.GetLength() > 0)
	{
		return false;
	}
	return true;
}
