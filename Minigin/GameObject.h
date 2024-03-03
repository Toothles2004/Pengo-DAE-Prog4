#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <glm/vec3.hpp>

class BasicComponent;
namespace dae
{
	class Texture2D;

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

		void SetLocalPosition(const glm::vec3& position);
		void SetLocalRotation(const glm::vec3& rotation);
		void SetLocalScale(const glm::vec3& scale);
		void SetPositionDirty() { m_PositionIsDirty = true; }
		void SetRotationDirty() { m_RotationIsDirty = true; }
		void SetScaleDirty() { m_ScaleIsDirty = true; }

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldRotation();
		const glm::vec3& GetLocalRotation() const { return m_LocalRotation; }
		const glm::vec3& GetWorldScale();
		const glm::vec3& GetLocalScale() const { return m_LocalScale; }

		void Rotate(const glm::vec3& rotation);
		void Scale(const glm::vec3& scale);

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const { return m_pParent; }
		size_t GetChildCount() const { return m_pChildren.size(); }
		GameObject* GetChildAt(unsigned int index) const;
		bool IsChild(GameObject* pChild) const;

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void UpdateWorldPosition();
		void UpdateWorldRotation();
		void UpdateWorldScale();

		bool m_ShouldDestroy = false;
		bool m_PositionIsDirty = false;
		bool m_RotationIsDirty = false;
		bool m_ScaleIsDirty = false;

		glm::vec3 m_WorldPosition;
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldRotation;
		glm::vec3 m_LocalRotation;
		glm::vec3 m_WorldScale;
		glm::vec3 m_LocalScale;

		GameObject* m_pParent = nullptr;
		std::vector<GameObject*> m_pChildren{};

		//Can only have 1 component of each type
		std::unordered_map<std::type_index, std::shared_ptr<BasicComponent>> m_pComponents{};
	};
}
