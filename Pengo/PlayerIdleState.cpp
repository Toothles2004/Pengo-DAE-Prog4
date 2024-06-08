#include "PlayerIdleState.h"

#include <glm/detail/func_geometric.inl>

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "MovementComponent.h"
#include "PlayerMovingState.h"
#include "RenderComponent.h"

::PlayerState* PlayerIdleState::HandleInput(glm::vec3 direction)
{
	if (glm::length(direction) > 0.01f)
	{
		m_Direction = glm::normalize(direction); // Normalize the direction for consistent movement
	}
	
	if (abs(m_Direction.x) >= 0.01f || abs(m_Direction.y) >= 0.01f)
	{
		PlayerMovingState* state = new PlayerMovingState();
		return state;
	}

	const auto state = this;
	return state;
}

void PlayerIdleState::OnEnter(glm::vec3 previousDir, dae::GameObject* owner)
{
	glm::vec2 characterFrameCount{ 40, 18 };
	if (owner == nullptr)
	{
		return;
	}
	
	if (previousDir.x > 0)
	{
		owner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{7, 0}, characterFrameCount);
	}
	else if (previousDir.x < 0)
	{
		owner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 3, 0 }, characterFrameCount);
	}
	else if (previousDir.y < 0)
	{
		owner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 4, 0 }, characterFrameCount);
	}
	else if (previousDir.y > 0)
	{
		owner->GetComponent<RenderComponent>()->SetTextureParameters(glm::vec2{ 0, 0 }, characterFrameCount);
	}
}

void PlayerIdleState::OnExit()
{
	
}
