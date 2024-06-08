#pragma once
#include "IceCubeState.h"

class IceCubeIdleState final : public IceCubeState
{
public:
	IceCubeIdleState() = default;
	~IceCubeIdleState() override = default;

	std::unique_ptr<IceCubeState> HandleInput(glm::vec3 direction) override;

	IceCubeIdleState(const IceCubeIdleState& other) = delete;
	IceCubeIdleState(IceCubeIdleState&& other) = delete;
	IceCubeIdleState& operator=(const IceCubeIdleState& other) = delete;
	IceCubeIdleState& operator=(IceCubeIdleState&& other) = delete;
};

