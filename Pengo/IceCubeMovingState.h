#pragma once
#include "IceCubeState.h"

class IceCubeMovingState final : public IceCubeState
{
public:
	IceCubeMovingState() = default;
	~IceCubeMovingState() override = default;

	std::unique_ptr<IceCubeState> Update() override;
	std::unique_ptr<IceCubeState> HandleInput(const glm::vec3 direction) override;
	void OnEnter(dae::GameObject* owner) override;

	IceCubeMovingState(const IceCubeMovingState& other) = delete;
	IceCubeMovingState(IceCubeMovingState&& other) = delete;
	IceCubeMovingState& operator=(const IceCubeMovingState& other) = delete;
	IceCubeMovingState& operator=(IceCubeMovingState&& other) = delete;

private:
	glm::vec3 m_Direction{};
	float m_MovementSpeed{ 100.f };
	dae::GameObject* m_pOwner{};
};

