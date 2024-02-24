#include "GameTime.h"
#include <windows.h>

GameTime::GameTime()
{
	DEVMODE dm;
	memset(&dm, 0, sizeof(dm));
	dm.dmSize = sizeof(dm);
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm) != 0)
	{
		m_MaxFPS = static_cast<float>(dm.dmDisplayFrequency);
	}
	m_MsPerFrame = static_cast<int>(1000.f / m_MaxFPS);
}

void GameTime::UpdateTime()
{
	const auto startTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(startTime - m_LastTime).count();
	m_LastTime = startTime;
}
