#pragma once
#include "Command.h"
#include "GameObject.h"

class DamageCommand : public daeEngine::Command
{
public:
	explicit DamageCommand(dae::GameObject* pActor);
	void Execute() override;

private:
	dae::GameObject* m_pActor;
};

