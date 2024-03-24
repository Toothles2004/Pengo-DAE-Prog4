#include "ScoreSubjectComponent.h"

ScoreSubjectComponent::ScoreSubjectComponent(dae::GameObject* owner)
	: BasicComponent(owner),
	m_Score(0)
{
	m_pEvent.emplace_back("GainPoints");
	m_pData.emplace("Score", m_Score);
}

void ScoreSubjectComponent::IncreaseScore(int amount)
{
	m_Score += amount;
	m_pData["Score"] = m_Score;
	Notify(m_pEvent[0]);
}
