#include "MovementCommand.h"
#include "PlayerComponent.h"

MovementCommand::MovementCommand(dae::GameObject* pActor, glm::vec3 direction)
	: m_Direction(direction),
	m_pActor(pActor)
{
}

void MovementCommand::Execute()
{
	m_pActor->GetComponent<PlayerComponent>()->SetDirection(m_Direction);
}
