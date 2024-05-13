#include "PlayerComponent.h"
#include "PlayerIdleState.h"

PlayerComponent::PlayerComponent(dae::GameObject* owner)
	: BasicComponent(owner),
	m_Direction(glm::vec3(0.f, 0.f, 0.f))
{
	m_State = std::make_unique<PlayerIdleState>();
	m_State->OnEnter(m_PreviousDirection, m_pOwner);
}

void PlayerComponent::Update()
{
	auto state = m_State->HandleInput(m_Direction);
	m_State->Update();
	if (state != m_State.get())
	{
		m_State->OnExit();
		m_State = std::move(std::unique_ptr<PlayerState>(state));
		m_State->OnEnter(m_PreviousDirection, m_pOwner);
	}
	m_PreviousDirection = m_Direction;
}

void PlayerComponent::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}
