#include "HealthSubjectComponent.h"
#include "HealthDisplayObserverComponent.h"

HealthSubjectComponent::HealthSubjectComponent(dae::GameObject* owner)
	: BasicComponent(owner),
	m_Health(4)
{
	m_pEvent.emplace_back("Damaged");
	m_pEvent.emplace_back("Died");

	m_pData.emplace("Health", m_Health);
}

void HealthSubjectComponent::Damage()
{
	if(m_Health > 0)
	{
		m_Health--;
		m_pData["Health"] = m_Health;
		if(m_Health == 0)
		{
			Notify(m_pEvent[1]);
		}
		else
		{
			Notify(m_pEvent[0]);
		}
	}
}


