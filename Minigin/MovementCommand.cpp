#include "MovementCommand.h"
#include "MovementComponent.h"

MovementCommand::MovementCommand(dae::GameObject* pActor, glm::vec3 direction)
	: Command(pActor),
	m_Direction(direction)
{
}

void MovementCommand::Execute()
{
	m_pActor->GetComponent<MovementComponent>()->Move(m_Direction);
}
