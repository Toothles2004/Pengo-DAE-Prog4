#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <memory>

class BasicComponent;
namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		template<typename T>
		void RemoveComponent();

		template<typename T>
		T* GetComponent();

		template <typename T>
		bool HasComponent() const;

		template<typename T, typename... Args>
		std::shared_ptr<T> AddComponent(Args&& ...);

		void MarkForDeath() { m_ShouldDestroy = true; }
		bool GetShouldDestroy() const { return m_ShouldDestroy; }

		/*void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);*/

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_ShouldDestroy = false;
		std::unordered_map<std::type_index, std::shared_ptr<BasicComponent>> m_pComponents{};
		//std::shared_ptr<Texture2D> m_texture{};
	};
}
