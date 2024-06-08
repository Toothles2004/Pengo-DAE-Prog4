#include "IceCubeMovingState.h"

#include <glm/detail/func_geometric.inl>

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "IceCubeIdleState.h"
#include "MovementComponent.h"

IceCubeState* IceCubeMovingState::Update()
{
	m_pOwner->GetComponent<MovementComponent>()->Move(m_Direction);

	if (m_pOwner->GetComponent<MovementComponent>()->IsAtTarget())
	{
		IceCubeIdleState* state = new IceCubeIdleState();
		return state;
	}

	const auto state = this;
	return state;
}

::IceCubeState* IceCubeMovingState::HandleInput(const glm::vec3 direction)
{
	if (glm::length(direction) > 0.01f)
	{
		m_Direction = glm::normalize(direction);
	}
	else
	{
		m_Direction = direction;
	}

	const auto state = this;
	return state;
}

void IceCubeMovingState::OnEnter(dae::GameObject* owner)
{
	m_pOwner = owner;
}
