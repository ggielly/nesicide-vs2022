#include "appsettings.h"

AppSettings* AppSettings::_instance = nullptr;

void AppSettings::setAppMode(AppMode mode)
{
	m_appMode = mode;

	emit appSettingsChanged();
}
