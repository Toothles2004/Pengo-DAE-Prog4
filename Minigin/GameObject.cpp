#include "GameObject.h"

#include <algorithm>
#include <glm/vec3.hpp>
#include "BasicComponent.h"

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition )
{
	if(IsChild(parent) || parent == this || m_pParent == parent)
	{
		return;
	}

	if (parent == nullptr)
	{
		if(keepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition());
			SetLocalRotation(GetWorldRotation());
			SetLocalScale(GetWorldScale());
		}

		SetPositionDirty();
		SetRotationDirty();
		SetScaleDirty();
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
			SetLocalRotation(GetLocalRotation() - parent->GetWorldRotation());
			SetLocalScale(GetLocalScale() / parent->GetWorldScale());
		}

		SetPositionDirty();
		SetRotationDirty();
		SetScaleDirty();
	}

	if (m_pParent != nullptr)
	{
		m_pParent->m_pChildren.erase(std::remove(m_pParent->m_pChildren.begin(), m_pParent->m_pChildren.end(), this));
	}

	m_pParent = parent;

	if (m_pParent != nullptr)
	{
		m_pParent->m_pChildren.emplace_back(this);
	}
}

dae::GameObject* dae::GameObject::GetChildAt(unsigned index) const
{
	if (index < m_pChildren.size())
	{
		return m_pChildren[index];
	}

	return nullptr;
}

bool dae::GameObject::IsChild(GameObject* pChild) const
{
	return std::ranges::any_of(m_pChildren, [pChild](GameObject* child) { return child == pChild; });
}

dae::GameObject::GameObject()
	: m_ShouldDestroy{ false },
	m_PositionIsDirty{ false },
	m_RotationIsDirty{ false },
	m_ScaleIsDirty{ false },
	m_WorldPosition{ 0.0f },
	m_LocalPosition{ 0.f },
	m_WorldRotation{ 0.0f },
	m_LocalRotation{ 0.0f },
	m_WorldScale{ 1.0f },
	m_LocalScale{ 1.0f },
	m_pParent{ nullptr }
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

void dae::GameObject::RenderImgui()
{
	for (const auto& component : m_pComponents)
	{
		component.second->RenderImgui();
	}
}

void dae::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	SetPositionDirty();
}

void dae::GameObject::SetLocalRotation(const glm::vec3& rotation)
{
	m_LocalRotation = rotation;
	SetRotationDirty();
}

void dae::GameObject::SetLocalScale(const glm::vec3& scale)
{
	m_LocalScale = scale;
	SetScaleDirty();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

const glm::vec3& dae::GameObject::GetWorldRotation()
{
	if (m_RotationIsDirty)
	{
		UpdateWorldRotation();
	}
	return m_WorldRotation;

}

const glm::vec3& dae::GameObject::GetWorldScale()
{
	if (m_ScaleIsDirty)
	{
		UpdateWorldScale();
	}
	return m_WorldScale;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_pParent == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
	}

	m_PositionIsDirty = false;
}

void dae::GameObject::UpdateWorldRotation()
{
	if (m_pParent == nullptr)
	{
		m_WorldRotation = m_LocalRotation;
	}
	else
	{
		m_WorldRotation = m_pParent->GetWorldRotation() + m_LocalRotation;
	}

	m_RotationIsDirty = false;
}

void dae::GameObject::UpdateWorldScale()
{
	if (m_pParent == nullptr)
	{
		m_WorldScale = m_LocalScale;
	}
	else
	{
		m_WorldScale = m_pParent->GetWorldScale() * m_LocalScale;
	}

	m_ScaleIsDirty = false;
}

void dae::GameObject::Rotate(const glm::vec3& rotation)
{
	m_LocalRotation = rotation;
}

void dae::GameObject::Scale(const glm::vec3& scale)
{
	m_LocalScale = scale;
}