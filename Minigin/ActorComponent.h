#pragma once
#include "BasicComponent.h"

namespace daeEngine
{
	class ActorComponent : public BasicComponent
	{
	public:
		explicit ActorComponent(dae::GameObject* owner)
			: BasicComponent(owner)
		{
		}

		~ActorComponent() = default;

		void SetCollidedObject(dae::GameObject* collidedObject)
		{
			m_pCollidedObject = collidedObject;
			if(!m_pCollidedObject)
			{
				m_IsColliding = false;
			}
			else
			{
				m_IsColliding = true;
			}
		}

		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent& operator=(ActorComponent&& other) = delete;

	protected:
		dae::GameObject* m_pCollidedObject{};
		bool m_IsColliding{ false };
	};
}
