#pragma once
#include "GameObject.h"

namespace daeEngine
{
	class Command
	{
	public:
		Command(dae::GameObject* actor);
		virtual ~Command() = default;
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

	protected:
		dae::GameObject* m_pActor;
	};
}

