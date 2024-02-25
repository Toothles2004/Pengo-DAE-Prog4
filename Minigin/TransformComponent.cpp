#include "TransformComponent.h"

TransformComponent::TransformComponent(dae::GameObject* owner)
	: BasicComponent(owner),
	m_Position(0.0f),
	m_Rotation(0.0f),
	m_Scale(1.0f)
{
}

TransformComponent::TransformComponent(dae::GameObject* owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: BasicComponent(owner),
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale)
{
}

void TransformComponent::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void TransformComponent::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void TransformComponent::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

void TransformComponent::Translate(const glm::vec3& translation)
{
	m_Position = translation;
}

void TransformComponent::Rotate(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void TransformComponent::Scale(const glm::vec3& scale)
{
	m_Scale = scale;
}
