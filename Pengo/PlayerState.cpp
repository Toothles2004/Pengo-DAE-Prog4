#include "PlayerState.h"
#include "GameObject.h"

PlayerState::PlayerState()
{
}

PlayerState::~PlayerState()
{
}

std::unique_ptr<PlayerState> PlayerState::Update()
{
	auto state = std::make_unique<PlayerState>();
	return state;
}

std::unique_ptr<PlayerState> PlayerState::HandleInput(glm::vec3)
{
	auto state = std::make_unique<PlayerState>();
	return state;
}
