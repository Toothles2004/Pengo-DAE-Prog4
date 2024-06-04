#include "PlayerMovingState.h"
#include "GameObject.h"
#include "PlayerIdleState.h"
#include "RenderComponent.h"

PlayerMovingState::~PlayerMovingState()
{
}

void PlayerMovingState::Update()
{
	auto position = m_pOwner->GetLocalTransform().position;
	position += m_Direction * m_MovementSpeed * daeEngine::GameTime::GetDeltaTime();
	m_pOwner->SetLocalPosition(position);
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
}

std::unique_ptr<PlayerState> PlayerMovingState::HandleInput(glm::vec3 direction)
{
	m_Direction = direction;
	if (abs(m_Direction.x) <= 0.01f && abs(m_Direction.y) <= 0.01f)
	{
		auto state = std::make_unique<PlayerIdleState>();
		return state;
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
