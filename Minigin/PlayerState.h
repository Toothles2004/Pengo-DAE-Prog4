#pragma once
#include <memory>
#include <glm/vec3.hpp>

namespace dae
{
	class GameObject;
}

class PlayerState
{
public:
	PlayerState();
	virtual ~PlayerState();

	virtual void Update();
	virtual std::unique_ptr<PlayerState> HandleInput(glm::vec3 direction);
	virtual void OnEnter(glm::vec3, dae::GameObject*) {}
	virtual void OnExit() {}

	PlayerState(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState& operator=(PlayerState&& other) = delete;

};
