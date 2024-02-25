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
		void RemoveComponent()
		{
			m_pComponents.erase(typeid(T));
		}

		template<typename T>
		std::weak_ptr<T> GetComponent()
		{
			if (const auto found = m_pComponents.find(typeid(T));
				found != m_pComponents.end())
			{
				return std::static_pointer_cast<T>(found->second);
			}

			return std::weak_ptr<T>();
		}

		template <typename T>
		bool HasComponent() const
		{
			const auto it = m_pComponents.find(typeid(T));
			return (it != m_pComponents.end());
		}

		template<typename T, typename... Args>
		std::shared_ptr<T> AddComponent(Args&& ... args)
		{
			static_assert(std::is_base_of<BasicComponent, T>::value, "T must derive from Component");

			auto newComponent = std::make_shared<T>(this, args...);
			m_pComponents.emplace(typeid(T), newComponent);
			return newComponent;
		}

		void MarkForDeath() { m_ShouldDestroy = true; }
		bool GetShouldDestroy() const { return m_ShouldDestroy; }

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_ShouldDestroy = false;

		//Can only have 1 component of each type
		std::unordered_map<std::type_index, std::shared_ptr<BasicComponent>> m_pComponents{};
	};
}
