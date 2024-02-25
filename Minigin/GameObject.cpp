#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BasicComponent.h"

template<typename T, typename... Args>
std::shared_ptr<T> dae::GameObject::AddComponent(Args&& ... args)
{
	static_assert(std::is_base_of<BasicComponent, T>::value, "T must derive from Component");

	auto newComponent = std::make_shared<T>(this, args...);
	m_pComponents.emplace(typeid(T), newComponent);
	return newComponent;
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

template<typename T>
void dae::GameObject::RemoveComponent()
{
	m_pComponents.erase(typeid(T));
}

template <typename T>
T* dae::GameObject::GetComponent()
{
	if (const auto found = m_pComponents.find(typeid(T));
		found != m_pComponents.end()) {
		return static_cast<T*>(found->second.get());
	}

	return nullptr;

}

template <typename T>
bool dae::GameObject::HasComponent() const
{
	const auto it = m_pComponents.find(typeid(T));
	return (it != m_pComponents.end());
}
