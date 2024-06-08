#pragma once
#include <glm/vec2.hpp>

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "IceCubeState.h"

class IceCubeBreakingState final : public IceCubeState
{
public:
	IceCubeBreakingState() = default;
	~IceCubeBreakingState() override = default;

	IceCubeState* Update() override;
	::IceCubeState* HandleInput(glm::vec3) override;
	void OnEnter(dae::GameObject* owner) override;

	IceCubeBreakingState(const IceCubeBreakingState& other) = delete;
	IceCubeBreakingState(IceCubeBreakingState&& other) = delete;
	IceCubeBreakingState& operator=(const IceCubeBreakingState& other) = delete;
	IceCubeBreakingState& operator=(IceCubeBreakingState&& other) = delete;

private:
	dae::GameObject* m_pOwner;
	glm::vec2 m_PositionInImage{0, 3};
	glm::vec2 m_FramesInImage{9, 4};
};

