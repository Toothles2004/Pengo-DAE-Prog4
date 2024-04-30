#pragma once
#include "SoundService.h"

namespace daeEngine
{
	class NullSoundService final : public SoundService
	{
	public:
		void LoadSound(const std::string& , int ) override {}
		void PlaySound(int, int , int , int ) override {}
	};
}
