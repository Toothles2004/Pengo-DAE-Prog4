#pragma once
#include "BasicComponent.h"
#include "BasicComponent.h"
#include "IceCubeState.h"

class IceCubeMovingState final : public IceCubeState
{
public:
	IceCubeMovingState() = default;
	~IceCubeMovingState() override = default;

	IceCubeState* Update() override;
	::IceCubeState* HandleInput(const glm::vec3 direction) override;
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

