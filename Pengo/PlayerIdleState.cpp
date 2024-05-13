#include "PlayerIdleState.h"

#include "PlayerMovingState.h"
#include "RenderComponent.h"

void PlayerIdleState::Update()
{
}

std::unique_ptr<PlayerState> PlayerIdleState::HandleInput(glm::vec3 direction)
{
	m_Direction = direction;
	
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
	m_pOwner = owner;
	if (previousDir.x > 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinRight.png");
	}
	else if (previousDir.x < 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinLeft.png");
	}
	else if (previousDir.y < 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinUp.png");
	}
	else if (previousDir.y > 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinDown.png");
	}
}

void PlayerIdleState::OnExit()
{
	
}
