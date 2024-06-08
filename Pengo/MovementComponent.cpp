#include "MovementComponent.h"
#include <glm/detail/func_geometric.inl>

MovementComponent::MovementComponent(dae::GameObject* owner, float speed, const int tileSize, const glm::vec2 offset)
	: BasicComponent(owner),
	m_MovementSpeed(speed),
	m_TargetPosition(owner->GetLocalTransform().position),
	m_IsMoving(false),
    m_TileSize(tileSize),
	m_Offset(offset)
{
}

void MovementComponent::Move(glm::vec3 direction)
{
    if (!m_IsMoving)
    {
        // Calculate current grid position
        const glm::vec3 currentPosition = m_pOwner->GetLocalTransform().position;
        const glm::vec3 gridPosition = WorldToGridPosition(currentPosition);

        // Determine the next grid position by adding the direction
        const glm::vec3 newGridPosition = gridPosition + direction;

        // Convert the new grid position to the target world position
        m_TargetPosition = GridToWorldPosition(newGridPosition);
        m_IsMoving = true;
    }

    if (m_IsMoving)
    {
        // Current position in the world
        const glm::vec3 currentPosition = m_pOwner->GetLocalTransform().position;

        // Compute the direction to the target position
        glm::vec3 movementDirection = m_TargetPosition - currentPosition;

        // Calculate distance to target
        const float distanceToTarget = glm::length(movementDirection);

        // Normalize the movement direction to get a unit vector if there's significant distance
        if (distanceToTarget > 0.01f)
        {
            movementDirection = glm::normalize(movementDirection);
        }

        // Calculate the movement vector scaled by speed and time
        glm::vec3 movement = movementDirection * m_MovementSpeed * daeEngine::GameTime::GetDeltaTime();

        // Move towards the target position
        if (distanceToTarget <= glm::length(movement))
        {
            // If the movement exceeds the distance to the target, snap to the target
            m_pOwner->SetLocalPosition(m_TargetPosition);
            m_IsMoving = false; // Movement complete
        }
        else
        {
            // Otherwise, move normally
            m_pOwner->SetLocalPosition(currentPosition + movement);
        }
    }
}

bool MovementComponent::IsAtTarget() const
{
    // Check if the player is at the target grid position
    return !m_IsMoving;
}

glm::vec3 MovementComponent::GridToWorldPosition(const glm::vec3& gridPosition) const
{
    return glm::vec3(
        gridPosition.x * static_cast<float>(m_TileSize) + m_Offset.x,
        gridPosition.y * static_cast<float>(m_TileSize) + m_Offset.y,
        gridPosition.z
    );
}

glm::vec3 MovementComponent::WorldToGridPosition(const glm::vec3& worldPosition) const
{
    return glm::vec3(
        std::floor((worldPosition.x - m_Offset.x) / static_cast<float>(m_TileSize)),
        std::floor((worldPosition.y - m_Offset.y) / static_cast<float>(m_TileSize)),
        worldPosition.z
    );
}