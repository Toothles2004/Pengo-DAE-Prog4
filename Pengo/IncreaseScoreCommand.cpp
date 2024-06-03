#include "IncreaseScoreCommand.h"
#include "ScoreSubjectComponent.h"

IncreaseScoreCommand::IncreaseScoreCommand(dae::GameObject* pActor, int amount)
	: m_ScoreIncrease(amount),
	m_pActor(pActor)
{
}

void IncreaseScoreCommand::Execute()
{
	m_pActor->GetComponent<ScoreSubjectComponent>()->IncreaseScore(m_ScoreIncrease);
}