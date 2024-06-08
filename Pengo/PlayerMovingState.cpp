#include "PlayerMovingState.h"

#include <glm/detail/func_geometric.inl>

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "PlayerIdleState.h"
#include "RenderComponent.h"

PlayerState* PlayerMovingState::Update()
{
	glm::vec2 characterFrameCount{ 40, 18 };
	m_pOwner->GetComponent<MovementComponent>()->Move(m_Direction);
	
	if (m_Direction.x > 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 6, 0 }, characterFrameCount);
	}
	else if (m_Direction.x < 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 2, 0 }, characterFrameCount);
	}
	else if (m_Direction.y < 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 5, 0 }, characterFrameCount);
	}
	else if (m_Direction.y > 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 1, 0 }, characterFrameCount);
	}
	else if (m_pOwner->GetComponent<MovementComponent>()->IsAtTarget())
	{
		PlayerIdleState* state = new PlayerIdleState();
		return state;
	}

	const auto state = this;
	return state;
}

::PlayerState* PlayerMovingState::HandleInput(glm::vec3 direction)
{
	if (glm::length(direction) > 0.01f)
	{
		m_Direction = glm::normalize(direction); // Normalize the direction for consistent movement
	}
	else
	{
		m_Direction = direction;
	}

	const auto state = this;
	return state;
}

void PlayerMovingState::OnEnter(glm::vec3, dae::GameObject* owner)
{
	m_pOwner = owner;
}
