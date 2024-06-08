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
	m_State->Update();
	if (state != m_State)
	{
		m_State->OnExit();
		m_State = std::move(state);
		m_State->OnEnter(m_pOwner);
	}
}

void IceCubeComponent::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}
