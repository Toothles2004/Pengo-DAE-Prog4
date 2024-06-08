#include "CollisionSubjectComponent.h"

#include "BoundingBox.h"
#include "CollisionObserverComponent.h"
#include "Scene.h"
#include "SceneManager.h"

CollisionSubjectComponent::CollisionSubjectComponent(dae::GameObject* owner)
	: BasicComponent(owner)
{
	m_pEvent.emplace_back("Collision");

	m_pData.emplace("CollidedObject1", m_pCollidedObject1);
	m_pData.emplace("CollidedObject2", m_pCollidedObject2);
}

void CollisionSubjectComponent::CheckCollision()
{
    std::vector<daeEngine::Observer*> observers = GetObservers();

    // Iterate through all observers
    for (size_t observer1Index{}; observer1Index < observers.size(); ++observer1Index)
    {
        //Cast to CollisionObserverComponent
        CollisionObserverComponent* observer1 = dynamic_cast<CollisionObserverComponent*>(observers[observer1Index]);
        if (!observer1) continue; // Skip if the cast fails

        //Get the bounding box of the first object
        daeEngine::BoundingBox boundsObserver1 = observer1->GetBoundingBox();

        for (size_t observer2Index = observer1Index + 1; observer2Index < observers.size(); ++observer2Index)
        {
            //Cast the second observer to CollisionObserverComponent
            CollisionObserverComponent* observer2 = dynamic_cast<CollisionObserverComponent*>(observers[observer2Index]);
            if (!observer2) continue; // Skip if the cast fails

            //Get the bounding box of the second object
            daeEngine::BoundingBox boundsObserver2 = observer2->GetBoundingBox();

            //Check for collision between bounding boxes
            if (boundsObserver1.Intersects(boundsObserver2))
            {
                //Create collision data
                m_pData["CollidedObject1"] = observer1->GetOwner();
                m_pData["CollidedObject2"] = observer2->GetOwner();

                //Notify both observers of the collision
                observer1->OnNotify(m_pData, m_pEvent[0]);
                observer2->OnNotify(m_pData, m_pEvent[0]);
            }
        }
    }
}

void CollisionSubjectComponent::Update()
{
	CheckCollision();
}
