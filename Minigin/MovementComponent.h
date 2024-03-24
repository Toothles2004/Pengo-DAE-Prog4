#pragma once
#include <glm/vec3.hpp>
#include "BasicComponent.h"

class MovementComponent : public daeEngine::BasicComponent
{
public:
	explicit MovementComponent(dae::GameObject* owner, float speed);

	void Move(glm::vec3 direction) const;

private:
	float m_MovementSpeed;
};

