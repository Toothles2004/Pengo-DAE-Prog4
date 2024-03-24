#include "IncreaseScoreCommand.h"
#include "ScoreSubjectComponent.h"

IncreaseScoreCommand::IncreaseScoreCommand(dae::GameObject* pActor, int amount)
	: Command(pActor),
	m_ScoreIncrease(amount)
{
}

void IncreaseScoreCommand::Execute()
{
	m_pActor->GetComponent<ScoreSubjectComponent>()->IncreaseScore(m_ScoreIncrease);
}