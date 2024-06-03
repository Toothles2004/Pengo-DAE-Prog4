#pragma once
#include "GameObject.h"
#include "Command.h"

class MovementCommand : public daeEngine::Command
{
public:
	explicit MovementCommand(dae::GameObject* pActor, glm::vec3 direction);
	void Execute() override;

private:
	glm::vec3 m_Direction;
	dae::GameObject* m_pActor;
};

