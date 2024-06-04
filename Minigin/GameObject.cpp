#include "GameObject.h"

#include <algorithm>
#include <glm/vec3.hpp>
#include "BasicComponent.h"

namespace dae
{
	void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
	{
		if (IsChild(parent) || parent == this || m_pParent == parent)
		{
			return;
		}

		if (parent == nullptr)
		{
			if (keepWorldPosition)
			{
				SetLocalPosition(GetWorldTransform().position);
				SetLocalRotation(GetWorldTransform().rotation);
				SetLocalScale(GetWorldTransform().scale);
			}

			SetTransformDirty();
		}
		else
		{
			if (keepWorldPosition)
			{
				SetLocalPosition(GetLocalTransform().position - parent->GetWorldTransform().position);
				SetLocalRotation(GetLocalTransform().rotation - parent->GetWorldTransform().rotation);
				SetLocalScale(GetLocalTransform().scale / parent->GetWorldTransform().scale);
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

	GameObject* GameObject::GetChildAt(unsigned index) const
	{
		if (index < m_pChildren.size())
		{
			return m_pChildren[index];
		}

		return nullptr;
	}

	bool GameObject::IsChild(GameObject* pChild) const
	{
		return std::ranges::any_of(m_pChildren, [pChild](GameObject* child) { return child == pChild; });
	}

	GameObject::GameObject()
		: m_ShouldDestroy{ false },
		m_TransformIsDirty{ false },
		m_WorldTransform{ {0.f, 0.f, 1.f}, 0.f, {1.f, 1.f, 1.f} },
		m_LocalTransform{ {0.f, 0.f, 1.f}, 0.f, {1.f, 1.f, 1.f} },
		m_pParent{ nullptr }
	{
	}

	GameObject::~GameObject() = default;

	void GameObject::Update()
	{
		for (const auto& component : m_pComponents)
		{
			component.second->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (const auto& component : m_pComponents)
		{
			component.second->FixedUpdate();
		}
	}
	void GameObject::LateUpdate()
	{
		for (const auto& component : m_pComponents)
		{
			component.second->LateUpdate();
		}
	}

	void GameObject::Render() const
	{
		for (const auto& component : m_pComponents)
		{
			component.second->Render();
		}
	}

	void GameObject::RenderImgui()
	{
		for (const auto& component : m_pComponents)
		{
			component.second->RenderImgui();
		}
	}

	void GameObject::SetLocalPosition(const glm::vec3& position)
	{
		m_LocalTransform.position = position;
		SetTransformDirty();
	}

	void GameObject::SetLocalRotation(const float rotation)
	{
		m_LocalTransform.rotation = rotation;
		SetTransformDirty();
	}

	void GameObject::SetLocalScale(const glm::vec3& scale)
	{
		m_LocalTransform.scale = scale;
		SetTransformDirty();
	}

	void GameObject::SetTransformDirty()
	{
		m_TransformIsDirty = true;
		for (auto child : m_pChildren)
		{
			child->SetTransformDirty();
		}
	}

	const GameObject::Transform& dae::GameObject::GetWorldTransform()
	{
		if (m_TransformIsDirty)
		{
			UpdateWorldTransform();
		}
		return m_WorldTransform;
	}

	void GameObject::UpdateWorldTransform()
	{
		if (m_pParent == nullptr)
		{
			m_WorldTransform = m_LocalTransform;
		}
		else
		{
			m_WorldTransform.position = m_pParent->GetWorldTransform().position + m_LocalTransform.position;
			m_WorldTransform.rotation = m_pParent->GetWorldTransform().rotation + m_LocalTransform.rotation;
			m_WorldTransform.scale = m_pParent->GetWorldTransform().scale + m_LocalTransform.scale;
		}

		m_TransformIsDirty = false;
	}
}