#include "BoundingBox.h"

namespace daeEngine
{
	BoundingBox::BoundingBox(glm::vec3 position, glm::vec3 size)
		: m_Position(position),
	m_Size(size)
	{
	}

	bool BoundingBox::Intersects(const BoundingBox& other) const
	{
		return
		(
			m_Position.x < other.m_Position.x + other.m_Size.x &&
			m_Position.x + m_Size.x > other.m_Position.x &&
			m_Position.y < other.m_Position.y + other.m_Size.y &&
			m_Position.y + m_Size.y > other.m_Position.y
		);
	}
}
