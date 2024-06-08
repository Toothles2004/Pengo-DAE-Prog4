#include "PlayerState.h"

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "GameObject.h"

PlayerState::PlayerState()
{
}

PlayerState::~PlayerState()
{
}

PlayerState* PlayerState::Update()
{
	const auto state = this;
	return state;
}

::PlayerState* PlayerState::HandleInput(glm::vec3)
{
	const auto state = this;
	return state;
}
