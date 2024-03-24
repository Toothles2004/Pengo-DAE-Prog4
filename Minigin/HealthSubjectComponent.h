#pragma once
#include "BasicComponent.h"
#include "Subject.h"

class HealthSubjectComponent : public daeEngine::Subject, public daeEngine::BasicComponent
{
public:
	explicit HealthSubjectComponent(dae::GameObject* owner);

	int GetLives() { return m_Health; }
	void Damage();

private:
	int m_Health;
	std::vector<std::string> m_pEvent;
};

