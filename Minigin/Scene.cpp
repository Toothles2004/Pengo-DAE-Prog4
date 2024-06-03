#include "Scene.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	for(auto& object : m_pObjects)
	{
		object->Update();
	}
}

void Scene::FixedUpdate()
{
	for (auto& object : m_pObjects)
	{
		object->FixedUpdate();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_pObjects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Scene::RenderImgui()
{
	for (const auto& object : m_pObjects)
	{
		object->RenderImgui();
	}
}

void Scene::DeleteGameObjects()
{
	m_pObjects.erase(std::remove_if(
		m_pObjects.begin(), 
		m_pObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) 
		{
			return obj->GetShouldDestroy();
		}),
		m_pObjects.end());
}


