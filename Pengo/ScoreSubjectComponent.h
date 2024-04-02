#pragma once
#include "BasicComponent.h"
#include "Subject.h"

class ScoreSubjectComponent : public daeEngine::Subject, public daeEngine::BasicComponent
{
public:
	explicit ScoreSubjectComponent(dae::GameObject* owner);

	int GetScore() { return m_Score; }
	void IncreaseScore(int amount);

private:
	int m_Score;
};

