#pragma once
#include <chrono>

#include "Singleton.h"

class GameTime final : public dae::Singleton<GameTime>
{
public:
	GameTime();
	void UpdateTime();

	float GetDeltaTime() const { return m_DeltaTime; }
	float GetFixedTimeStep() const { return m_FixedTimeStep; }
	float GetMaxFPS() { return m_MaxFPS; }
	int GetMsPerFrame() { return m_MsPerFrame; }

private:
	friend class dae::Singleton<GameTime>;

	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime = std::chrono::high_resolution_clock::now();
	float m_DeltaTime = 0.0f;
	float m_FixedTimeStep = 0.02f;
	float m_MaxFPS = 60.0f;
	int m_MsPerFrame;
};

