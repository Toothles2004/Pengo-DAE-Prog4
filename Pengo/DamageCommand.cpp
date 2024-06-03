#include "DamageCommand.h"
#include "HealthSubjectComponent.h"

DamageCommand::DamageCommand(dae::GameObject* pActor)
	: m_pActor(pActor)
{
}

void DamageCommand::Execute()
{
	m_pActor->GetComponent<HealthSubjectComponent>()->Damage();
}
