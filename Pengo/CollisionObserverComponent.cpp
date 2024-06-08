#include "CollisionObserverComponent.h"
#include "ActorComponent.h"

CollisionObserverComponent::CollisionObserverComponent(dae::GameObject* owner)
	: BasicComponent(owner)
{
	if (owner->HasComponent<daeEngine::ActorComponent>() == false)
	{
		owner->AddComponent<daeEngine::ActorComponent>();
	}
	m_pActorComponent = m_pOwner->GetComponent<daeEngine::ActorComponent>();
}

void CollisionObserverComponent::OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event)
{
	if (event == "Collision")
	{
		dae::GameObject* collidedObject1 = std::any_cast<dae::GameObject*>(data["CollidedObject1"]);
		dae::GameObject* collidedObject2 = std::any_cast<dae::GameObject*>(data["CollidedObject2"]);

		if (collidedObject1 == m_pOwner && collidedObject2 != nullptr)
		{
			m_pActorComponent->SetCollidedObject(collidedObject2);
			auto actor = collidedObject2->GetComponent<daeEngine::ActorComponent>();
			if (actor) actor->SetCollidedObject(collidedObject1);
		}
		if(collidedObject2 == m_pOwner && collidedObject1 != nullptr)
		{
			m_pActorComponent->SetCollidedObject(collidedObject1);
			auto actor = collidedObject1->GetComponent<daeEngine::ActorComponent>();
			if (actor) actor->SetCollidedObject(collidedObject2);
		}
	}
}

daeEngine::BoundingBox CollisionObserverComponent::GetBoundingBox()
{
	const glm::vec3 position = m_pOwner->GetLocalTransform().position;
	const glm::vec3 scale = m_pOwner->GetLocalTransform().scale;
	const glm::vec3 size = glm::vec3(16 * scale.x, 16 * scale.y, 1.f);

	return daeEngine::BoundingBox{ position, size };
}
