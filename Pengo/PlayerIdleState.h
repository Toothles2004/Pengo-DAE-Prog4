#pragma once
#include "PlayerState.h"

class PlayerIdleState final : public PlayerState
{
public:
	PlayerIdleState() = default;
	~PlayerIdleState() override = default;

	void Update() override;
	PlayerState* HandleInput(glm::vec3 direction) override;
	void OnEnter(glm::vec3 previousDir, dae::GameObject* owner) override;
	void OnExit() override;

	PlayerIdleState(const PlayerIdleState& other) = delete;
	PlayerIdleState(PlayerIdleState&& other) = delete;
	PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& other) = delete;

private:
	glm::vec3 m_Direction;
	dae::GameObject* m_pOwner;
};

