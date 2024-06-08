#include "IceCubeState.h"
#include "GameObject.h"

IceCubeState::IceCubeState()
{
}

IceCubeState::~IceCubeState()
{
}

std::unique_ptr<IceCubeState> IceCubeState::Update()
{
	auto state = std::make_unique<IceCubeState>();
	return state;
}

std::unique_ptr<IceCubeState> IceCubeState::HandleInput(glm::vec3)
{
	auto state = std::make_unique<IceCubeState>();
	return state;
}