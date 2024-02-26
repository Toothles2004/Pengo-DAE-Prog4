#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_pScenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (auto& scene : m_pScenes)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (auto& scene : m_pScenes)
	{
		scene->LateUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::DeleteGameObjects()
{
	for (auto& scene : m_pScenes)
	{
		scene->DeleteGameObjects();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	return *scene;
}
