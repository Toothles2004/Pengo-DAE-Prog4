#include "SDLSoundService.h"

#include <deque>
#include <mutex>
#include <SDL_mixer.h>
#include <thread>
#include <unordered_map>
#include <vector>

namespace daeEngine
{
	struct SoundSettings
	{
		int channel{};
		int id{};
		int volume{};
		int loops{};
	};

	class SDLSoundService::SoundServiceImpl
	{
	public:
		explicit SoundServiceImpl(int amountOfChannels)
		{
			m_AmountOfChannels = std::max(1, amountOfChannels);
			if (Mix_Init(MIX_INIT_MP3) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				// Handle initialization error
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, m_AmountOfChannels, 2048) < 0)
			{
				printf("SDL_mixer could not open audio! SDL_mixer Error: %s\n", Mix_GetError());
				// Handle audio opening error
			}

			m_LoadSoundThread = std::jthread{ [&] { LoadSoundToMap(); } };
			m_PlaySoundThread = std::jthread{ [&] {PlaySoundsInQueue(); } };
		}

		~SoundServiceImpl()
		{
			if (m_PlaySoundThread.joinable())
			{
				m_PlaySoundThread.join();
			}

			if (m_LoadSoundThread.joinable())
			{
				m_LoadSoundThread.join();
			}

			for (const auto& music : m_pMusic)
			{
				Mix_FreeChunk(music.second);
			}
			Mix_CloseAudio();
			Mix_Quit();
			m_ShouldPlaySounds = false;
		}

		void LoadSoundToQueue(const std::string& filename, int id)
		{
			std::lock_guard<std::mutex> musicQueueLock3(m_MusicMutex);
			m_LoadQueue.emplace_back(id, filename);
		}

		void LoadSoundToMap()
		{
			while (m_ShouldPlaySounds)
			{
				if (!m_LoadQueue.empty())
				{
					std::lock_guard<std::mutex> musicQueueLock2(m_MusicMutex);
					std::pair<int, std::string> sound = m_LoadQueue.front();
					m_LoadQueue.pop_front();

					auto it = m_pMusic.find(sound.first);
					if (it != m_pMusic.end())
					{
						m_pMusic[sound.first] = Mix_LoadWAV(sound.second.c_str());
					}
					else
					{
						m_pMusic.emplace(std::make_pair(sound.first, Mix_LoadWAV(sound.second.c_str())));
					}

					if (m_pMusic[sound.first] == NULL)
					{
						printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
						// Handle loading error
					}
				}
			}
		}

		void PlaySound(const SoundSettings& settings, int channel)
		{
			std::lock_guard<std::mutex> musicQueueLock(m_MusicMutex);
			auto it = m_pMusic.find(settings.id);
			if (it->second != NULL)
			{
				Mix_Volume(channel, settings.volume);
				//-1 is infinite loops
				Mix_PlayChannel(channel, m_pMusic[settings.id], settings.loops);
			}
			else
			{
				printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
				// Handle playing error
			}
		}

		void AddSoundToQueue(int channel, int id, int volume, int loops)
		{
			std::lock_guard<std::mutex> soundQueueLock(m_QueueMutex);
			m_SoundQueue.push_back({ channel, id, volume, loops });
		}

		void PlaySoundsInQueue()
		{
			SoundSettings sound = SoundSettings();

			while (m_ShouldPlaySounds)
			{
				bool foundSound{ false };
				if (m_QueueMutex.try_lock())
				{
					if (!m_SoundQueue.empty())
					{
						sound = m_SoundQueue.front();
						if (const auto it = m_pMusic.find(sound.id); it == m_pMusic.end())
						{
							m_QueueMutex.unlock();
							continue;
						}
						m_SoundQueue.pop_front();
						foundSound = true;
					}
					m_QueueMutex.unlock();
				}

				if (foundSound)
				{
					PlaySound(sound, sound.channel);
				}
			}
		}

		SoundServiceImpl(const SoundServiceImpl& other) = delete;
		SoundServiceImpl(SoundServiceImpl&& other) = delete;
		SoundServiceImpl& operator=(const SoundServiceImpl& other) = delete;
		SoundServiceImpl& operator=(SoundServiceImpl&& other) = delete;

	private:
		std::unordered_map<int, Mix_Chunk*> m_pMusic;
		std::jthread m_PlaySoundThread;
		std::jthread m_LoadSoundThread;
		std::deque<SoundSettings> m_SoundQueue;
		std::deque<std::pair<int, std::string>> m_LoadQueue;
		bool m_ShouldPlaySounds{ true };
		int m_AmountOfChannels{ 0 };

		std::mutex m_QueueMutex;
		std::mutex m_MusicMutex;
		std::mutex m_ChannelMutex;
	};

	SDLSoundService::SDLSoundService(int amountOfChannels)
		: m_pImpl{ std::make_unique<SoundServiceImpl>(amountOfChannels) }
	{
	}

	SDLSoundService::~SDLSoundService() = default;

	void SDLSoundService::LoadSound(const std::string& filename, int id)
	{
		m_pImpl->LoadSoundToQueue(filename, id);
	}

	void SDLSoundService::PlaySound(int channel, int id, int volume, int amountOfLoops)
	{
		m_pImpl->AddSoundToQueue(channel, id, volume, amountOfLoops);
	}
}
