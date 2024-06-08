#include "PlayerIdleState.h"

#include <glm/detail/func_geometric.inl>

#include "MovementComponent.h"
#include "PlayerMovingState.h"
#include "RenderComponent.h"

std::unique_ptr<PlayerState> PlayerIdleState::HandleInput(glm::vec3 direction)
{
	if (glm::length(direction) > 0.01f)
	{
		m_Direction = glm::normalize(direction); // Normalize the direction for consistent movement
	}
	
	if (abs(m_Direction.x) >= 0.01f || abs(m_Direction.y) >= 0.01f)
	{
		auto state = std::make_unique<PlayerMovingState>();
		return state;
	}

	auto state = std::make_unique<PlayerIdleState>();
	return state;
}

void PlayerIdleState::OnEnter(glm::vec3 previousDir, dae::GameObject* owner)
{
	if (owner == nullptr)
	{
		return;
	}
	
	if (previousDir.x > 0)
	{
		owner->GetComponent<RenderComponent>()->SetTexture("textures/penguinRight.png");
	}
	else if (previousDir.x < 0)
	{
		owner->GetComponent<RenderComponent>()->SetTexture("textures/penguinLeft.png");
	}
	else if (previousDir.y < 0)
	{
		owner->GetComponent<RenderComponent>()->SetTexture("textures/penguinUp.png");
	}
	else if (previousDir.y > 0)
	{
		owner->GetComponent<RenderComponent>()->SetTexture("textures/penguinDown.png");
	}
}

void PlayerIdleState::OnExit()
{
	
}
