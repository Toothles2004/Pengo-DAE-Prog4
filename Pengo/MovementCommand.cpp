#include "MovementCommand.h"
#include "PlayerComponent.h"

MovementCommand::MovementCommand(dae::GameObject* pActor, glm::vec3 direction)
	: Command(pActor),
	m_Direction(direction)
{
}

void MovementCommand::Execute()
{
	m_pActor->GetComponent<PlayerComponent>()->SetDirection(m_Direction);
}
