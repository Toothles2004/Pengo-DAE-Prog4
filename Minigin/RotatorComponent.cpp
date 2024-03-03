#include "RotatorComponent.h"
#include <cmath>

RotatorComponent::RotatorComponent(dae::GameObject* owner, float radius, float speed)
	: BasicComponent( owner ),
	m_OrbitingRadius{ radius },
	m_OrbitingSpeed{ speed },
	m_Angle{ 0.f }
{

}

void RotatorComponent::Update()
{
	auto& time = GameTime::GetInstance();
	glm::vec3 pos{};

	m_Angle += m_OrbitingSpeed * time.GetDeltaTime();

	pos.x = m_OrbitingRadius * cos(m_Angle);
	pos.y = m_OrbitingRadius * sin(m_Angle);

	m_pOwner->SetLocalPosition(pos);
}
