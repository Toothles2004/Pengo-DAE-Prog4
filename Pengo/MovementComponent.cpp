#include "MovementComponent.h"

MovementComponent::MovementComponent(dae::GameObject* owner, float speed)
	: BasicComponent(owner),
	m_MovementSpeed(speed)
{
}

void MovementComponent::Move(glm::vec3 direction) const
{
	auto position = m_pOwner->GetLocalTransform().position;
	position += direction * m_MovementSpeed * daeEngine::GameTime::GetDeltaTime();
	m_pOwner->SetLocalPosition(position);
}