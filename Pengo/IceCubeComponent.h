#pragma once
#include "ActorComponent.h"
#include "IceCubeState.h"

class IceCubeComponent final : public daeEngine::ActorComponent
{
public:
	IceCubeComponent(dae::GameObject* owner);
	~IceCubeComponent() override = default;

	void Update() override;
	void SetDirection(glm::vec3 direction);

	IceCubeComponent(const IceCubeComponent& other) = delete;
	IceCubeComponent(IceCubeComponent&& other) = delete;
	IceCubeComponent& operator=(const IceCubeComponent& other) = delete;
	IceCubeComponent& operator=(IceCubeComponent&& other) = delete;

private:
	std::unique_ptr<IceCubeState> m_State;
	glm::vec3 m_Direction;
};

