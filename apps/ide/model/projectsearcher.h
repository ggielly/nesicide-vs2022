#ifndef PROJECTSEARCHER_H
#define PROJECTSEARCHER_H

#include "cnesicideproject.h"

namespace ProjectSearcher
{
	// ------------------------------------------------------------------------
	// Use this functions to find data items of a specific type.
	// ------------------------------------------------------------------------

	template <class T>
	QList<QUuid> findUuidsOfType(CNesicideProject* project)
	{
		QList<QUuid> items;
		const char* targetName = T::staticMetaObject.className();

		IProjectTreeViewItemIterator iter(project);
		while (iter.current() != nullptr)
		{
			auto item = dynamic_cast<CProjectBase*>(iter.current());
			if (item != nullptr)
			{
				const char* className = item->metaObject()->className();
				if (strcmp(className, targetName) == 0)
				{
					items.append(item->uuid());
				}
			}
			iter.next();
		}
		return items;
	}

	template <class T>
	QList<T*> findItemsOfType(CNesicideProject* project)
	{
		QList<T*> items;
		const char* targetName = T::staticMetaObject.className();

		IProjectTreeViewItemIterator iter(project);
		while (iter.current() != nullptr)
		{
			auto item = dynamic_cast<CProjectBase*>(iter.current());
			if (item != nullptr)
			{
				const char* className = item->metaObject()->className();
				if (strcmp(className, targetName) == 0)
				{
					items.append(static_cast<T*>(item));
				}
			}
			iter.next();
		}
		return items;
	}

	template <class T>
	T* findItemByUuid(CNesicideProject* project, const QUuid& uuid)
	{
		const char* targetName = T::staticMetaObject.className();

		IProjectTreeViewItemIterator iter(project);
		while (iter.current() != nullptr)
		{
			if (iter.current()->uuid() == uuid.toString())
			{
				auto item = dynamic_cast<CProjectBase*>(iter.current());
				if (item == nullptr)
					return nullptr;

				// Check if object has the correct class.
				const char* className = item->metaObject()->className();
				if (strcmp(className, targetName) == 0)
				{
					return static_cast<T*>(item);
				}
				else
				{
					return nullptr;
				}
			}
			iter.next();
		}
		return nullptr;
	}

	template <class T>
	bool uuidIsOfType(CNesicideProject* project, const QUuid& uuid)
	{
		return findItemByUuid<T>(project, uuid) != nullptr;
	}
}
#endif // PROJECTSEARCHER_H
