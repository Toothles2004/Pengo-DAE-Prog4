#include "PlayerState.h"
#include "GameObject.h"

PlayerState::PlayerState()
{
}

PlayerState::~PlayerState()
{
}

void PlayerState::Update()
{
}

std::unique_ptr<PlayerState> PlayerState::HandleInput(glm::vec3)
{
	auto state = std::make_unique<PlayerState>();
	return state;
}
