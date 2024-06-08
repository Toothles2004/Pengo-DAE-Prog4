#include "IceCubeComponent.h"

#include "IceCubeIdleState.h"

IceCubeComponent::IceCubeComponent(dae::GameObject* owner)
	: BasicComponent(owner),
	m_Direction(glm::vec3(0.f, 0.f, 0.f))
{
	m_State = std::make_unique<IceCubeIdleState>();
	m_State->OnEnter(m_pOwner);
}

void IceCubeComponent::Update()
{
	auto state = m_State->HandleInput(m_Direction);
	auto state2 = m_State->Update();
	if (state != m_State.get() && state != nullptr)
	{
		m_State->OnExit();
		m_State = std::unique_ptr<IceCubeState>(state);
		m_State->OnEnter(m_pOwner);
	}
	else if (state2 != m_State.get() && state != nullptr)
	{
		m_State->OnExit();
		m_State = std::unique_ptr<IceCubeState>(state2);
		m_State->OnEnter(m_pOwner);
	}
}

void IceCubeComponent::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}
