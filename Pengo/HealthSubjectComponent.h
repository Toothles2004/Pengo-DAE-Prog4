#pragma once
#include "BasicComponent.h"
#include "Subject.h"

class HealthSubjectComponent final : public daeEngine::Subject, public daeEngine::BasicComponent
{
public:
	explicit HealthSubjectComponent(dae::GameObject* owner, int health);

	int GetLives() const { return m_Health; }
	void Damage();

private:
	int m_Health;
	
};

