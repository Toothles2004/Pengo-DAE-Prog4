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

		SetTransformDirty();
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
			SetLocalRotation(GetLocalRotation() - parent->GetWorldRotation());
			SetLocalScale(GetLocalScale() / parent->GetWorldScale());
		}

		SetTransformDirty();
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
	m_TransformIsDirty{ false },
	m_WorldTransform{ {0.f, 0.f, 1.f} },
	m_LocalTransform{ {0.f, 0.f, 1.f} },
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
	m_LocalTransform.position = position;
	SetTransformDirty();
}

void dae::GameObject::SetLocalRotation(const glm::vec3& rotation)
{
	m_LocalTransform.rotation = rotation;
	SetTransformDirty();
}

void dae::GameObject::SetLocalScale(const glm::vec3& scale)
{
	m_LocalTransform.scale = scale;
	SetTransformDirty();
}

void dae::GameObject::SetTransformDirty()
{
	m_TransformIsDirty = true;
	for (auto child : m_pChildren)
	{
		child->SetTransformDirty();
	}
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_TransformIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldTransform.position;
}

const glm::vec3& dae::GameObject::GetWorldRotation()
{
	if (m_TransformIsDirty)
	{
		UpdateWorldRotation();
	}
	return m_WorldTransform.rotation;

}

const glm::vec3& dae::GameObject::GetWorldScale()
{
	if (m_TransformIsDirty)
	{
		UpdateWorldScale();
	}
	return m_WorldTransform.scale;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_pParent == nullptr)
	{
		m_WorldTransform.position = m_LocalTransform.position;
	}
	else
	{
		m_WorldTransform.position = m_pParent->GetWorldPosition() + m_LocalTransform.position;
	}

	m_TransformIsDirty = false;
}

void dae::GameObject::UpdateWorldRotation()
{
	if (m_pParent == nullptr)
	{
		m_WorldTransform.rotation = m_LocalTransform.rotation;
	}
	else
	{
		m_WorldTransform.rotation = m_pParent->GetWorldRotation() + m_LocalTransform.rotation;
	}

	m_TransformIsDirty = false;
}

void dae::GameObject::UpdateWorldScale()
{
	if (m_pParent == nullptr)
	{
		m_WorldTransform.scale = m_LocalTransform.scale;
	}
	else
	{
		m_WorldTransform.scale = m_pParent->GetWorldScale() * m_LocalTransform.scale;
	}

	m_TransformIsDirty = false;
}

void dae::GameObject::Rotate(const glm::vec3& rotation)
{
	m_LocalTransform.rotation = rotation;
}

void dae::GameObject::Scale(const glm::vec3& scale)
{
	m_LocalTransform.scale = scale;
}