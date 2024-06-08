#include "IceCubeBreakingState.h"

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "RenderComponent.h"

IceCubeState* IceCubeBreakingState::Update()
{
	if(m_PositionInImage.x < m_FramesInImage.x)
	{
		m_pOwner->GetComponent<RenderComponent>()->SetTextureParameters(m_PositionInImage, m_FramesInImage);
		++m_PositionInImage;
	}
	else
	{
		m_pOwner->MarkForDeath();
	}

	const auto state = this;
	return state;
}

::IceCubeState* IceCubeBreakingState::HandleInput(glm::vec3)
{
	const auto state = this;
	return state;
}

void IceCubeBreakingState::OnEnter(dae::GameObject* owner)
{
	m_pOwner = owner;
}
