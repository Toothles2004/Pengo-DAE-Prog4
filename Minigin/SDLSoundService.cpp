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

			for(int index{}; index < m_AmountOfChannels; ++index)
			{
				m_PlaySoundThread.emplace_back(std::jthread{ [&] {PlaySoundsInQueue(); } });
				m_SoundQueue.emplace_back(std::deque<SoundSettings>());
			}
		}

		~SoundServiceImpl()
		{
			for (const auto& music : m_pMusic)
			{
				Mix_FreeChunk(music.second);
			}
			Mix_CloseAudio();
			Mix_Quit();
			m_ShouldPlaySounds = false;
		}

		void LoadSound(const std::string& filename, int id)
		{
			
			auto it = m_pMusic.find(id);
			if (it != m_pMusic.end()) 
			{
				m_pMusic[id] = Mix_LoadWAV(filename.c_str());
			}
			else 
			{
				m_pMusic.emplace(std::make_pair(id, Mix_LoadWAV(filename.c_str())));
			}

			if (m_pMusic[id] == NULL)
			{
				printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
				// Handle loading error
			}
		}

		void PlaySound(const SoundSettings& settings, int channel)
		{
			auto it = m_pMusic.find(settings.id);
			if(it->second != NULL)
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
			m_SoundQueue[channel].push_back({id, volume, loops});
		}

		void PlaySoundsInQueue()
		{
			m_ChannelMutex.lock();
			int channel = m_ThreadChannels;
			m_ThreadChannels++;
			m_ChannelMutex.unlock();


			while (m_ShouldPlaySounds)
			{
				m_QueueMutex.lock();
				SoundSettings sound = SoundSettings();
				bool foundSound{ false };
				if (!m_SoundQueue[channel].empty())
				{
					sound = m_SoundQueue[channel].front();
					if (const auto it = m_pMusic.find(sound.id); it == m_pMusic.end())
					{
						continue;
					}
					m_SoundQueue[channel].pop_front();
					foundSound = true;
				}
				m_QueueMutex.unlock();
				if (foundSound)
				{
					PlaySound(sound, channel);
				}
			}
		}

		SoundServiceImpl(const SoundServiceImpl& other) = delete;
		SoundServiceImpl(SoundServiceImpl&& other) = delete;
		SoundServiceImpl& operator=(const SoundServiceImpl& other) = delete;
		SoundServiceImpl& operator=(SoundServiceImpl&& other) = delete;

	private:
		std::unordered_map<int, Mix_Chunk*> m_pMusic;
		std::vector<std::jthread> m_PlaySoundThread;
		std::vector<std::deque<SoundSettings>> m_SoundQueue;
		bool m_ShouldPlaySounds{ true };
		int m_CurrentChannelPlaying{ -1 };
		int m_AmountOfChannels{ 0 };
		std::mutex m_QueueMutex;

		std::mutex m_ChannelMutex;
		int m_ThreadChannels{ 0 };
	};

	SDLSoundService::SDLSoundService(int amountOfChannels)
		: m_pImpl{ std::make_unique<SoundServiceImpl>(amountOfChannels) }
	{
	}

	SDLSoundService::~SDLSoundService() = default;

	void SDLSoundService::LoadSound(const std::string& filename, int id)
	{
		m_pImpl->LoadSound(filename, id);
	}

	void SDLSoundService::PlaySound(int channel, int id, int volume, int amountOfLoops)
	{
		m_pImpl->AddSoundToQueue(channel, id, volume, amountOfLoops);
	}
}
