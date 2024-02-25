#pragma once
#include <glm/vec3.hpp>

#include "BasicComponent.h"

class TransformComponent : public BasicComponent
{
public:
	explicit TransformComponent(dae::GameObject* owner);
	explicit TransformComponent(dae::GameObject* owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetRotation() const { return m_Rotation; }
	const glm::vec3& GetScale() const { return m_Scale;  }

	void Translate(const glm::vec3& translation);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

