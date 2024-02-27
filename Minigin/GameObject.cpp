#include <string>
#include "GameObject.h"

#include <glm/vec3.hpp>

#include "ResourceManager.h"
#include "Renderer.h"
#include "BasicComponent.h"

void dae::GameObject::SetParent(GameObject* , bool )
{
	/*if (IsChild(parent) || parent == this || m_parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
		SetPositionDirty()
	}
	if (m_parent) m_parent->RemoveChild(this);
	m_parent = parent;
	if (m_parent) m_parent->AddChild(this);*/
}

dae::GameObject::GameObject()
	: m_Position(0.0f),
	m_Rotation(0.0f),
	m_Scale(1.0f)
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (const auto& component : m_pComponents)
	{
		component.second->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (const auto& component : m_pComponents)
	{
		component.second->FixedUpdate();
	}
}
void dae::GameObject::LateUpdate()
{
	for (const auto& component : m_pComponents)
	{
		component.second->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component.second->Render();
	}
}

void dae::GameObject::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void dae::GameObject::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void dae::GameObject::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

void dae::GameObject::Translate(const glm::vec3& translation)
{
	m_Position = translation;
}

void dae::GameObject::Rotate(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

void dae::GameObject::Scale(const glm::vec3& scale)
{
	m_Scale = scale;
}