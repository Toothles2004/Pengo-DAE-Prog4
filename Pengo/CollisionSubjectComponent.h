#pragma once
#include "BasicComponent.h"
#include "Subject.h"

class CollisionSubjectComponent final : public daeEngine::Subject, public daeEngine::BasicComponent
{
public:
	explicit CollisionSubjectComponent(dae::GameObject* owner);

	void CheckCollision();
	void Update() override;

private:
	dae::GameObject* m_pCollidedObject1{};
	dae::GameObject* m_pCollidedObject2{};
};

