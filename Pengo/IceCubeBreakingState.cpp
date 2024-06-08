#include "IceCubeBreakingState.h"
#include "RenderComponent.h"

std::unique_ptr<IceCubeState> IceCubeBreakingState::Update()
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

	auto state = std::make_unique<IceCubeBreakingState>();
	return state;
}

std::unique_ptr<IceCubeState> IceCubeBreakingState::HandleInput(glm::vec3 direction)
{
	auto state = std::make_unique<IceCubeBreakingState>();
	return state;
}

void IceCubeBreakingState::OnEnter(dae::GameObject* owner)
{
	m_pOwner = owner;
}
