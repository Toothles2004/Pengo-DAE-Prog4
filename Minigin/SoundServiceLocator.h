#pragma once
#include <memory>

#include "NullSoundService.h"
#include "SDLSoundService.h"

namespace daeEngine
{
	class SoundServiceLocator final
	{
	public:
		static SoundService& GetSoundService() { return *m_SoundServiceInstance; }
		static void RegisterSoundService(std::unique_ptr<SoundService>&& soundService)
		{
			m_SoundServiceInstance = soundService == nullptr ? std::make_unique<NullSoundService>() : std::move(soundService);
		}

	private:
		inline static std::unique_ptr<SoundService> m_SoundServiceInstance{std::make_unique<SDLSoundService>(1)};
	};
}


