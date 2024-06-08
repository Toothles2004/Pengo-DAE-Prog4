#include "PlayerMovingState.h"

#include <glm/detail/func_geometric.inl>

#include "GameObject.h"
#include "MovementComponent.h"
#include "PlayerIdleState.h"
#include "RenderComponent.h"

PlayerMovingState::~PlayerMovingState()
{
}

std::unique_ptr<PlayerState> PlayerMovingState::Update()
{
	m_pOwner->GetComponent<MovementComponent>()->Move(m_Direction);
	/*auto position = m_pOwner->GetLocalTransform().position;
	position += m_Direction * m_MovementSpeed * daeEngine::GameTime::GetDeltaTime();
	m_pOwner->SetLocalPosition(position);*/
	if (m_Direction.x > 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinWalkRight.png");
	}
	else if (m_Direction.x < 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinWalkLeft.png");
	}
	else if (m_Direction.y < 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinWalkUp.png");
	}
	else if (m_Direction.y > 0)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTexture("textures/penguinWalkDown.png");
	}

	if (m_pOwner->GetComponent<MovementComponent>()->IsAtTarget())
	{
		auto state = std::make_unique<PlayerIdleState>();
		return state;
	}

	auto state = std::make_unique<PlayerMovingState>();
	return state;
}

std::unique_ptr<PlayerState> PlayerMovingState::HandleInput(glm::vec3 direction)
{
	if (glm::length(direction) > 0.01f)
	{
		m_Direction = glm::normalize(direction); // Normalize the direction for consistent movement
	}
	else
	{
		m_Direction = direction;
	}

	auto state = std::make_unique<PlayerMovingState>();
	return state;
}

void PlayerMovingState::OnEnter(glm::vec3, dae::GameObject* owner)
{
	m_pOwner = owner;
}

void PlayerMovingState::OnExit()
{
	
}
