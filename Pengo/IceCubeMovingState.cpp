#include "IceCubeMovingState.h"

#include <glm/detail/func_geometric.inl>

#include "IceCubeIdleState.h"
#include "MovementComponent.h"

std::unique_ptr<IceCubeState> IceCubeMovingState::Update()
{
	m_pOwner->GetComponent<MovementComponent>()->Move(m_Direction);

	if (m_pOwner->GetComponent<MovementComponent>()->IsAtTarget())
	{
		auto state = std::make_unique<IceCubeIdleState>();
		return state;
	}

	auto state = std::make_unique<IceCubeMovingState>();
	return state;
}

std::unique_ptr<IceCubeState> IceCubeMovingState::HandleInput(const glm::vec3 direction)
{
	if (glm::length(direction) > 0.01f)
	{
		m_Direction = glm::normalize(direction);
	}
	else
	{
		m_Direction = direction;
	}

	auto state = std::make_unique<IceCubeMovingState>();
	return state;
}

void IceCubeMovingState::OnEnter(dae::GameObject* owner)
{
	m_pOwner = owner;
}
