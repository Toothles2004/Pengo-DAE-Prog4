#include "MovementComponent.h"

MovementComponent::MovementComponent(dae::GameObject* owner, float speed)
	: BasicComponent(owner),
	m_MovementSpeed(speed)
{
}

void MovementComponent::Move(glm::vec3 direction) const
{
	auto position = m_pOwner->GetLocalPosition();
	position += direction * m_MovementSpeed * GameTime::GetDeltaTime();
	m_pOwner->SetLocalPosition(position);
}


