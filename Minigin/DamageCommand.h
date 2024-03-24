#pragma once
#include "Command.h"

class DamageCommand : public daeEngine::Command
{
public:
	explicit DamageCommand(dae::GameObject* pActor);
	void Execute() override;
};

