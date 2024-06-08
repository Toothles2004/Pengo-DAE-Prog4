#include "SceneManager.h"
#include "Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace dae
{
	void SceneManager::Update()
	{
		if (m_pActiveScene)
		{
			m_pActiveScene->Update();
		}
	}

	void SceneManager::FixedUpdate()
	{
		if (m_pActiveScene)
		{
			m_pActiveScene->FixedUpdate();
		}
	}

	void SceneManager::LateUpdate()
	{
		if (m_pActiveScene)
		{
			m_pActiveScene->LateUpdate();
		}
	}

	void SceneManager::Render()
	{
		if (m_pActiveScene)
		{
			m_pActiveScene->Render();
		}
	}

	void SceneManager::RenderImgui()
	{
		if (m_pActiveScene)
		{
			m_pActiveScene->RenderImgui();
		}
	}

	void SceneManager::DeleteGameObjects()
	{
		if (m_pActiveScene)
		{
			m_pActiveScene->DeleteGameObjects();
		}
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto& scene = std::shared_ptr<Scene>(new Scene(name));
		m_pScenes.push_back(scene);
		return *scene;
	}

	std::vector<std::vector<int>> SceneManager::ReadLevelLayoutFromFile(const std::string& filename)
	{
		std::ifstream file(filename);
		std::vector<std::vector<int>> layout;
		std::string line;

		while (std::getline(file, line))
		{
			if (!line.empty() && line[0] != '"' && line[0] != ';')
			{
				std::istringstream iss(line);
				std::vector<int> row;

				char valueChar;
				while (iss >> valueChar)
				{
					if (isdigit(valueChar))
					{
						int value = valueChar - '0';
						if (value >= 0 && value <= 5)
						{
							row.push_back(value);
						}
					}
				}

				layout.push_back(row);
			}
		}

		return layout;
	}

	void SceneManager::SetActiveScene(const std::string& name)
	{
		for (const auto& scene : m_pScenes)
		{
			if (scene->GetName() == name)
			{
				m_pActiveScene = scene.get();
				break;
			}
		}
	}
}
