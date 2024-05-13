#pragma once
#include "BasicComponent.h"
#include "PlayerState.h"

class PlayerComponent final : public daeEngine::BasicComponent
{
public:
	PlayerComponent(dae::GameObject* owner);
	~PlayerComponent() override = default;

	void Update() override;
	void SetDirection(glm::vec3 direction);

	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) = delete;

private:
	std::unique_ptr<PlayerState> m_State;
	glm::vec3 m_Direction;
	glm::vec3 m_PreviousDirection{};
};

