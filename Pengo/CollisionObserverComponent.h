#pragma once
#include "BasicComponent.h"
#include "BoundingBox.h"
#include "Observer.h"

namespace daeEngine
{
	class ActorComponent;
}

class HealthSubjectComponent;
class CollisionObserverComponent : public daeEngine::Observer, public daeEngine::BasicComponent
{
public:
	explicit CollisionObserverComponent(dae::GameObject* owner);

	dae::GameObject* GetOwner() const { return m_pOwner; }

	void OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event) override;
	daeEngine::BoundingBox GetBoundingBox();

private:
	daeEngine::ActorComponent* m_pActorComponent{};

};

