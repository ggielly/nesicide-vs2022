#include "cprojecttabwidget.h"

#include "cdesignereditorbase.h"
#include "cdockwidgetregistry.h"
#include "ccc65interface.h"

#include "cprojecttreeopenaction.h"
#include "model/projectsearcher.h"

#include "environmentsettingsdialog.h"

#include <QToolButton>

CProjectTabWidget::CProjectTabWidget(QWidget* parent) :
	QTabWidget(parent)
{
	tabBar()->installEventFilter(this);
	tabBar()->setMouseTracking(true);
	tabBar()->setVisible(EnvironmentSettingsDialog::useTabBarInEditorArea());
}

void CProjectTabWidget::setProjectModel(CProjectModel* model)
{
	m_pProjectModel = model;
}

bool CProjectTabWidget::eventFilter(QObject* object, QEvent* event)
{
	if (object == tabBar())
	{
		if (event->type() == QEvent::ContextMenu)
		{
			auto cmEvent = dynamic_cast<QContextMenuEvent*>(event);
			tabBar_contextMenuEvent(cmEvent);
			return true;
		}
		else if (event->type() == QEvent::MouseMove)
		{
			auto mmEvent = dynamic_cast<QMouseEvent*>(event);
			tabBar_mouseMoveEvent(mmEvent);
			return true;
		}
	}
	return false;
}

void CProjectTabWidget::tabBar_mouseMoveEvent(QMouseEvent*/*event*/)
{
}

void CProjectTabWidget::tabBar_contextMenuEvent(QContextMenuEvent* event)
{
	// Make sure tab under pointer is current...
	setCurrentWidget(widget(tabBar()->tabAt(event->pos())));

	auto editor = dynamic_cast<CDesignerEditorBase*>(widget(currentIndex()));
	QMenu menu;

	QString addToProjectText = "Add to ";
	addToProjectText += CNesicideProject::instance()->getProjectTitle();
	addToProjectText += " project...";

	QString removeFromProjectText = "Remove from ";
	removeFromProjectText += CNesicideProject::instance()->getProjectTitle();
	removeFromProjectText += " project...";

	QStringList extensions;
	extensions += EnvironmentSettingsDialog::sourceExtensionsForC().split(" ", QString::SkipEmptyParts);
	extensions += EnvironmentSettingsDialog::sourceExtensionsForAssembly().split(" ", QString::SkipEmptyParts);
	extensions += EnvironmentSettingsDialog::customExtensions().split(" ", QString::SkipEmptyParts);

	if ((editor) &&
		(!editor->treeLink()))
	{
		menu.addAction(addToProjectText);
	}
	else if ((editor) &&
		(editor->treeLink()))
	{
		menu.addAction(removeFromProjectText);
	}

	QAction* action = menu.exec(event->globalPos());
	QString fileName = tabBar()->tabText(currentIndex());
	QDir dir(QDir::currentPath());

	if (action && (action->text() == addToProjectText))
	{
		foreach(QString ext, extensions)
		{
			if (fileName.endsWith(ext, Qt::CaseInsensitive))
			{
				CNesicideProject::instance()->getProject()->getSources()->addSourceFile(fileName);
				break;
			}
		}
	}
	else if (action && (action->text() == removeFromProjectText))
	{
	}
}

int CProjectTabWidget::addTab(QWidget* page, const QIcon& icon, const QString& label)
{
	auto editor = dynamic_cast<CDesignerEditorBase*>(page);
	auto codeBrowser = dynamic_cast<QDockWidget*>(CDockWidgetRegistry::instance()->getWidget("Assembly Browser"));
	QIcon myIcon;
	int tabIdx;

	if (editor)
	{
		QObject::connect(codeBrowser,SIGNAL(snapToTab(QString)), this,SLOT(snapToTab(QString)));
		QObject::connect(editor,SIGNAL(editor_modified(bool)), this,SLOT(tabModified(bool)));
		QObject::connect(editor,SIGNAL(markProjectDirty(bool)), this,SLOT(projectDirtied(bool)));
		QObject::connect(editor,SIGNAL(snapToTab(QString)), this,SLOT(snapToTab(QString)));
		QObject::connect(editor,SIGNAL(applyChanges(QString)), this,SLOT(applyChanges(QString)));
		QObject::connect(m_pProjectModel,SIGNAL(itemRemoved(QUuid)), editor,SLOT(itemRemoved(QUuid)));
		QObject::connect(m_pProjectModel,SIGNAL(itemAdded(QUuid)), editor,SLOT(itemAdded(QUuid)));
		QObject::connect(this,SIGNAL(snapTo(QString)), editor,SLOT(snapTo(QString)));
		QObject::connect(this,SIGNAL(applyChangesToTab(QString)), editor,SLOT(applyChangesToTab(QString)));
		QObject::connect(this,SIGNAL(applyProjectPropertiesToTab()), editor,SLOT(applyProjectPropertiesToTab()));
		QObject::connect(this,SIGNAL(applyEnvironmentSettingsToTab()), editor,SLOT(applyEnvironmentSettingsToTab()));
		QObject::connect(this,SIGNAL(applyAppSettingsToTab()), editor,SLOT(applyAppSettingsToTab()));
		QObject::connect(this,SIGNAL(checkOpenFile(QDateTime)), editor,SLOT(checkOpenFile(QDateTime)));
		QObject::connect(editor,SIGNAL(addStatusBarWidget(QWidget*)), this,SIGNAL(addStatusBarWidget(QWidget*)));
		QObject::connect(editor,SIGNAL(removeStatusBarWidget(QWidget*)), this,SIGNAL(removeStatusBarWidget(QWidget*)));
		QObject::connect(editor,SIGNAL(setStatusBarMessage(QString)), this,SIGNAL(setStatusBarMessage(QString)));
		QObject::connect(editor,SIGNAL(addToolBarWidget(QToolBar*)), this,SIGNAL(addToolBarWidget(QToolBar*)));
		QObject::connect(editor,SIGNAL(removeToolBarWidget(QToolBar*)), this,SIGNAL(removeToolBarWidget(QToolBar*)));
		QObject::connect(this,SIGNAL(updateTargetMachine(QString)), editor,SLOT(updateTargetMachine(QString)));
	}

	myIcon = icon;
	// Having a custom icon causes unnecessary and weird text eliding.
	//   if ( editor && editor->treeLink() )
	//   {
	//      myIcon = editor->treeLink()->icon();
	//   }
	//   else
	//   {
	//      myIcon = QIcon(":/resources/icons8-file.png");
	//   }
	tabIdx = QTabWidget::addTab(page, myIcon, label);
	//   QToolButton *pButton = new QToolButton();
	//   pButton->setObjectName(label);
	//   pButton->setMaximumSize(16,16);
	//   pButton->setIcon(QIcon(":/resources/icons8-pin.png"));
	//   QObject::connect(pButton,SIGNAL(pressed()),this,SLOT(unDockTab()));
	//   tabBar()->setTabButton(tabIdx,QTabBar::RightSide,pButton);

	//   QToolButton* closeButton = new QToolButton;
	//   QStyle* closeButtonStyle = closeButton->style();
	//   QPixmap closePixmap = closeButtonStyle->standardPixmap(QStyle::SP_DockWidgetCloseButton);
	//   closeButton->setIcon(QIcon(closePixmap));
	//   closeButton->setAutoRaise(true);
	//   closeButton->setContentsMargins(0,0,0,0);
	//   tabBar()->setTabButton(tabIdx,QTabBar::RightSide,closeButton);

	emit tabAdded(tabIdx);

	return tabIdx;
}

void CProjectTabWidget::unDockTab()
{
	//   QToolButton *pButton = dynamic_cast<QToolButton*>(sender());
	//   QString      name = pButton->objectName();
	//   int tab;

	//   for ( tab = 0; tab < count(); tab++ )
	//   {
	//      if ( tabBar()->tabText(tab) == name )
	//      {
	//         QWidget *detach = new QWidget(nullptr);
	//         detach->setWindowTitle(name);
	//         detach->setGeometry(widget(tab)->geometry());
	//         blockSignals(true);
	//         QGridLayout *layout = new QGridLayout();
	//         layout->addWidget(widget(tab));
	//         detach->setLayout(layout);
	//         blockSignals(false);
	//         detach->show();
	//         tearOffs.insert(name,detach);
	//         break;
	//      }
	//   }
}

void CProjectTabWidget::reDockTab()
{
	//   QWidget *attach = dynamic_cast<QWidget*>(sender());
	//   if ( attach )
	//   {
	//      tearOffs.remove(attach->windowTitle());
	//      blockSignals(true);
	//      int tab = addTab(attach,attach->windowTitle());
	//      blockSignals(false);
	//      attach->close();
	//      attach->deleteLater();
	//   }
}

int CProjectTabWidget::addTab(QWidget* page, const QString& label)
{
	return addTab(page, QIcon(), label);
}

void CProjectTabWidget::removeTab(int index)
{
	emit tabAboutToBeRemoved(index);
	QTabWidget::removeTab(index);
}

void CProjectTabWidget::tabModified(bool modified)
{
	int tab;

	for (tab = 0; tab < count(); tab++)
	{
		if (widget(tab) == sender())
		{
			if (modified)
			{
				if (tabBar()->tabText(tab).right(1) != "*")
				{
					tabBar()->setTabText(tab, tabBar()->tabText(tab) + "*");
				}
			}
			else
			{
				if (tabBar()->tabText(tab).right(1) == "*")
				{
					tabBar()->setTabText(tab, tabBar()->tabText(tab).left(tabBar()->tabText(tab).length() - 1));
				}
			}

			emit tabModified(tab, modified);
		}
	}
}

void CProjectTabWidget::projectDirtied(bool dirtied)
{
	emit markProjectDirty(dirtied);
}

void CProjectTabWidget::snapToTab(QString item)
{
	int tab;
	QStringList splits;
	uint32_t addr;
	uint32_t absAddr;
	QList<CSourceItem*> sources = ProjectSearcher::findItemsOfType<CSourceItem>(CNesicideProject::instance());
	QList<CGraphicsBank*> gfxBanks = ProjectSearcher::findItemsOfType<CGraphicsBank>(CNesicideProject::instance());
	QList<CTileStamp*> tileStamps = ProjectSearcher::findItemsOfType<CTileStamp>(CNesicideProject::instance());
	bool found = false;
	bool open = false;
	QDir dir;
	QDir projectDir = QDir::currentPath();
	QFile fileIn;
	QString file;
	QString filePath;
	QString uuid;
	QString symbol;
	CDesignerEditorBase* editor = NULL;

	qDebug(item.toUtf8().data());
	// Make sure item is something we care about
	if (item.startsWith("Address,"))
	{
		splits = item.split(QRegExp("[,():]"), QString::SkipEmptyParts);
		if (splits.count() == 2)
		{
			addr = splits.at(1).toInt(NULL, 16);
			absAddr = addr;
		}
		else if (splits.count() == 3)
		{
			addr = splits.at(2).toInt(NULL, 16);
			absAddr = addr;
		}
		else if (splits.count() == 4)
		{
			addr = splits.at(3).toInt(NULL, 16);
			absAddr = (splits.at(1).toInt(NULL, 16) * MEM_8KB) + splits.at(2).toInt(NULL, 16);
		}
		file = QDir::cleanPath(CCC65Interface::instance()->getSourceFileFromPhysicalAddress(addr, absAddr));
	}
	else if (item.startsWith("SourceNavigatorFile,"))
	{
		splits = item.split(QRegExp("[,]"));
		file = QDir::cleanPath(splits.at(1));
	}
	else if (item.startsWith("OutputPaneFile,"))
	{
		splits = item.split(QRegExp("[,]"));
		file = QDir::cleanPath(splits.at(1));
	}
	else if (item.startsWith("Tile,"))
	{
		splits = item.split(QRegExp("[,]"));
		uuid = splits.at(1);
	}

	if (!uuid.isEmpty())
	{
		for (tab = 0; tab < count(); tab++)
		{
			if (file == tabBar()->tabText(tab))
			{
				setCurrentIndex(tab);
				found = true;
				open = true;
				break;
			}
		}

		for (tab = 0; tab < tearOffs.count(); tab++)
		{
			if (file == tearOffs.keys().at(tab))
			{
				tearOffs.values().at(tab)->show();
				found = true;
				open = true;
				break;
			}
		}

		// File is not open, search the project.
		if (!found)
		{
			CProjectTreeOpenAction action(this, m_pProjectModel);
			m_pProjectModel->visitDataItem(uuid, action);
		}
	}

	if (!file.isEmpty())
	{
		for (tab = 0; tab < count(); tab++)
		{
			if (file == tabBar()->tabText(tab))
			{
				setCurrentIndex(tab);
				found = true;
				open = true;
				break;
			}
		}

		for (tab = 0; tab < tearOffs.count(); tab++)
		{
			if (file == tearOffs.keys().at(tab))
			{
				tearOffs.values().at(tab)->show();
				found = true;
				open = true;
				break;
			}
		}

		// File is not open, search the project.
		if (!found)
		{
			foreach(CSourceItem* source, sources)
			{
				if (source->path() == file)
				{
					source->openItemEvent(this);
					found = true;
					open = true;
					break;
				}
			}
		}
		if (!found)
		{
			foreach(CGraphicsBank* source, gfxBanks)
			{
				if (source->caption() == file)
				{
					source->openItemEvent(this);
					found = true;
					open = true;
					break;
				}
			}
		}
		if (!found)
		{
			foreach(CTileStamp* source, tileStamps)
			{
				if (source->caption() == file)
				{
					source->openItemEvent(this);
					found = true;
					open = true;
					break;
				}
			}
		}

		// If we got here we can't find the file in the project, search the project
		// directory.
		if (!found)
		{
			dir.setPath(QDir::currentPath());
			filePath = dir.relativeFilePath(file);
			fileIn.setFileName(filePath);

			if (fileIn.exists())
			{
				found = true;
			}
		}

		// If we got here we might be looking for a source file that's part of a library.
		// Search the source paths...
		if (!found)
		{
			QStringList sourcePaths = CNesicideProject::instance()->getSourceSearchPaths();

			foreach(QString searchDir, sourcePaths)
			{
				dir = searchDir;
				filePath = dir.filePath(file);
				fileIn.setFileName(filePath);

				for (int tab = 0; tab < count(); tab++)
				{
					if (tabBar()->tabText(tab) == filePath)
					{
						setCurrentWidget(widget(tab));
						found = true;
						open = true;
					}
				}

				for (int tab = 0; tab < tearOffs.count(); tab++)
				{
					if (filePath == tearOffs.keys().at(tab))
					{
						tearOffs.values().at(tab)->show();
						found = true;
						open = true;
						break;
					}
				}

				if (fileIn.exists())
				{
					found = true;
					break;
				}
			}
		}

		// If we got here we can't find the damn thing, ask the user to help.
		if (!found)
		{
			QString str;
			str.sprintf("Locate %s...", file.toLatin1().constData());
			QString newDir = QFileDialog::getOpenFileName(0, str, QDir::currentPath(), QString(),NULL,
			                                              QFileDialog::DontUseNativeDialog);
			if (!newDir.isEmpty())
			{
				QFileInfo fileInfo(newDir);
				dir = projectDir.relativeFilePath(fileInfo.path());
				CNesicideProject::instance()->addSourceSearchPath(dir.path());
				filePath = dir.filePath(file);
				fileIn.setFileName(filePath);

				if (fileIn.exists())
				{
					found = true;
				}
			}
		}

		// Try to open the file.
		if (found && (!open) &&
			fileIn.open(QIODevice::ReadOnly))
		{
			// If the file is a source file, open it using the CodeEditorForm.
			QStringList extensions = EnvironmentSettingsDialog::sourceExtensionsForC().split(
				" ", QString::SkipEmptyParts);
			extensions.append(
				EnvironmentSettingsDialog::sourceExtensionsForAssembly().split(" ", QString::SkipEmptyParts));
			extensions.append(EnvironmentSettingsDialog::customExtensions().split(" ", QString::SkipEmptyParts));
			foreach(QString ext, extensions)
			{
				if (fileIn.fileName().endsWith(ext, Qt::CaseInsensitive))
				{
					editor = new CodeEditorForm(fileIn.fileName(), QString(fileIn.readAll()));
					break;
				}
			}
			// If the file isn't opened by the above, check if it's a CHR file and
			// if so, open it using the CHRROMDisplayDialog.
			if (!editor)
			{
				if (fileIn.fileName().endsWith(".chr", Qt::CaseInsensitive))
				{
					editor = new CHRROMDisplayDialog(false, (qint8*)fileIn.readAll().constData());
				}
			}
			// If we still haven't opened the damn thing, throw it at a CodeEditorForm
			// to see what we get.
			if (!editor)
			{
				editor = new CodeEditorForm(fileIn.fileName(), QString(fileIn.readAll()));
			}

			fileIn.close();

			if (editor)
			{
				addTab(editor, fileIn.fileName());
				setCurrentWidget(editor);
			}
		}
	}

	emit snapTo(item);
}

void CProjectTabWidget::applyChanges(QString uuid)
{
	qDebug("applyChanges: %s", uuid.toUtf8().data());
	emit applyChangesToTab(uuid);
}

void CProjectTabWidget::applyProjectProperties()
{
	emit applyProjectPropertiesToTab();
}

void CProjectTabWidget::applyEnvironmentSettings()
{
	tabBar()->setVisible(EnvironmentSettingsDialog::useTabBarInEditorArea());
	emit applyEnvironmentSettingsToTab();
}

void CProjectTabWidget::applyAppSettings()
{
	emit applyAppSettingsToTab();
}

void CProjectTabWidget::checkOpenFiles(QDateTime lastActivationTime)
{
	emit checkOpenFile(lastActivationTime);
}
