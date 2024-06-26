#pragma once
#include "BasicComponent.h"
#include "BasicComponent.h"
#include "PlayerState.h"

class PlayerMovingState final : public PlayerState
{
public:
	PlayerMovingState() = default;
	~PlayerMovingState() override = default;

	PlayerState* Update() override;
	::PlayerState* HandleInput(glm::vec3 direction) override;
	void OnEnter(glm::vec3 previousDir, dae::GameObject* owner) override;

	PlayerMovingState(const PlayerMovingState& other) = delete;
	PlayerMovingState(PlayerMovingState&& other) = delete;
	PlayerMovingState& operator=(const PlayerMovingState& other) = delete;
	PlayerMovingState& operator=(PlayerMovingState&& other) = delete;

private:
	glm::vec3 m_Direction{};
	float m_MovementSpeed{100.f};
	dae::GameObject* m_pOwner{};
};