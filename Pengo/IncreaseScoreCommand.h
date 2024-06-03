#pragma once
#include "Command.h"
#include "GameObject.h"

class IncreaseScoreCommand : public daeEngine::Command
{
public:
	explicit IncreaseScoreCommand(dae::GameObject* pActor, int amount);
	void Execute() override;

private:
	int m_ScoreIncrease;
	dae::GameObject* m_pActor;
};

