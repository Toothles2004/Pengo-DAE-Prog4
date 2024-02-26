#pragma once
#include <chrono>
#include "Singleton.h"

class GameTime final : public dae::Singleton<GameTime>
{
public:
	static void UpdateTime();
	static void SetFPS();

	static float GetDeltaTime() { return m_DeltaTime; }
	static float GetFixedTimeStep() { return m_FixedTimeStep; }
	static float GetMaxFPS() { return m_MaxFPS; }
	static int GetMsPerFrame() { return m_MsPerFrame; }

private:

	inline static std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime = std::chrono::high_resolution_clock::now();
	inline static float m_DeltaTime = 0.0f;
	inline static float m_FixedTimeStep = 0.02f;
	inline static float m_MaxFPS = 60.0f;
	inline static int m_MsPerFrame;
};

