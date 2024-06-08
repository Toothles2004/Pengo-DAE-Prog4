#include "PlayerComponent.h"
#include "PlayerIdleState.h"

PlayerComponent::PlayerComponent(dae::GameObject* owner)
	: ActorComponent(owner),
	m_Direction(glm::vec3(0.f, 0.f, 0.f))
{
	m_State = std::make_unique<PlayerIdleState>();
	m_State->OnEnter(m_PreviousDirection, m_pOwner);
}

void PlayerComponent::Update()
{
	PlayerState* state = m_State->HandleInput(m_Direction);
	PlayerState* state2 = m_State->Update();
	if (state != m_State.get() && state != nullptr)
	{
		m_State->OnExit();
		m_State = std::unique_ptr<PlayerState>(state);
		m_State->OnEnter(m_PreviousDirection, m_pOwner);
	}
	else if(state2 != m_State.get() && state != nullptr)
	{
		m_State->OnExit();
		m_State = std::unique_ptr<PlayerState>(state2);
		m_State->OnEnter(m_PreviousDirection, m_pOwner);
	}
	if(m_Direction != glm::vec3(0.f, 0.f, 0.f))
	{
		m_PreviousDirection = m_Direction;
	}
}

void PlayerComponent::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}
