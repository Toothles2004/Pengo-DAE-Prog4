#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();
		void RenderImgui();
		void DeleteGameObjects();
		std::vector<std::vector<int>> ReadLevelLayoutFromFile(const std::string& filename);

		void SetActiveScene(const std::string& name);
		Scene* GetActiveScene() const { return m_pActiveScene; }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		Scene* m_pActiveScene{ nullptr };
	};
}
