#pragma once
#include "Command.h"

class MovementCommand : public daeEngine::Command
{
public:
	explicit MovementCommand(dae::GameObject* pActor, glm::vec3 direction);
	void Execute() override;

private:
	glm::vec3 m_Direction;

};

