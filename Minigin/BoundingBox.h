#pragma once
#include <glm/vec3.hpp>

namespace daeEngine
{
    class BoundingBox
    {
    public:
        BoundingBox(glm::vec3 position, glm::vec3 size);

        glm::vec3 GetPosition() const { return m_Position; }
        glm::vec3 GetSize() const { return m_Size; }

        // Check if this bounding box intersects with another
        bool Intersects(const BoundingBox& other) const;

    private:
        glm::vec3 m_Position{};
        glm::vec3 m_Size{};
    };
}
