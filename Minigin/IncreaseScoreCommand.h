#pragma once
#include "Command.h"

class IncreaseScoreCommand : public daeEngine::Command
{
public:
	explicit IncreaseScoreCommand(dae::GameObject* pActor, int amount);
	void Execute() override;

private:
	int m_ScoreIncrease;
};

