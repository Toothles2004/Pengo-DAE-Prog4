#pragma once
#include <string>


namespace daeEngine
{
	class SoundService
	{
	public:
		explicit SoundService() = default;
		virtual ~SoundService() = default;

		virtual void LoadSound(const std::string& filename, int id) = 0;
		virtual void PlaySound(int channel, int id, int volume = 100, int amountOfLoops = 0) = 0;

		SoundService(const SoundService& other) = delete;
		SoundService(SoundService&& other) = delete;
		SoundService& operator=(const SoundService& other) = delete;
		SoundService& operator=(SoundService&& other) = delete;
	};
}
