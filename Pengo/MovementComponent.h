#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "BasicComponent.h"

class MovementComponent : public daeEngine::BasicComponent
{
public:
	explicit MovementComponent(dae::GameObject* owner, float speed, const int tileSize, const glm::vec2 offset);

	void Move(glm::vec3 direction);
	bool IsAtTarget() const;

private:
	glm::vec3 GridToWorldPosition(const glm::vec3& gridPosition) const;
	glm::vec3 WorldToGridPosition(const glm::vec3& worldPosition) const;

	float m_MovementSpeed;
	glm::vec3 m_TargetPosition;
	bool m_IsMoving;
	const int m_TileSize;
	const glm::vec2 m_Offset;

};