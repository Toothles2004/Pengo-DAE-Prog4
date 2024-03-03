#pragma once
#include <glm/vec2.hpp>
#include "BasicComponent.h"

class RotatorComponent : public BasicComponent
{
public:
	explicit RotatorComponent(dae::GameObject* owner, float radius, float speed);

	void Update() override;


private:
	float m_OrbitingRadius;
	float m_OrbitingSpeed;
	float m_Angle;
};

