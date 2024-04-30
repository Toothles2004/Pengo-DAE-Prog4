#pragma once
#include <memory>
#include "SoundService.h"

namespace daeEngine
{
	class SDLSoundService : public SoundService
	{
	public:
		explicit SDLSoundService(int amountOfChannels);
		virtual~SDLSoundService() override;

		void LoadSound(const std::string& filename, int id) override;
		void PlaySound(int channel, int id, int volume = 100, int amountOfLoops = 0) override;

		SDLSoundService(const SDLSoundService& other) = delete;
		SDLSoundService(SDLSoundService&& other) = delete;
		SDLSoundService& operator=(const SDLSoundService& other) = delete;
		SDLSoundService& operator=(SDLSoundService&& other) = delete;

	private:
		class SoundServiceImpl;
		std::unique_ptr<SoundServiceImpl> m_pImpl;
	};
}
