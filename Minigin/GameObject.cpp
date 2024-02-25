#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BasicComponent.h"

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