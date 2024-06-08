#pragma once
#include <memory>
#include <glm/vec3.hpp>

namespace dae
{
	class GameObject;
}

class IceCubeState
{
public:
	IceCubeState();
	virtual ~IceCubeState();

	virtual std::unique_ptr<IceCubeState> Update();
	virtual std::unique_ptr<IceCubeState> HandleInput(glm::vec3 direction);
	virtual void OnEnter(dae::GameObject*) {}
	virtual void OnExit() {}

	IceCubeState(const IceCubeState& other) = delete;
	IceCubeState(IceCubeState&& other) = delete;
	IceCubeState& operator=(const IceCubeState& other) = delete;
	IceCubeState& operator=(IceCubeState&& other) = delete;
};

