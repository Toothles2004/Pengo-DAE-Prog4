#include "FPSComponent.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* owner)
    : BasicComponent( owner ),
    m_RefreshRate{ 1.f },
    m_Timer{ m_RefreshRate },
	m_FrameCount{}
{
    if(owner->HasComponent<TextComponent>() == false)
    {
	    owner->AddComponent<TextComponent>();
    }

    m_pTextComponent = owner->GetComponent<TextComponent>();
}

void FPSComponent::Update()
{
    const float deltaT = GameTime::GetDeltaTime();
    if (deltaT <= 0.f)
    {
        return;
    }

    m_Timer += deltaT;
    m_FrameCount++;

    if (m_Timer >= m_RefreshRate)
    {
        if(const auto sharedPtr = m_pTextComponent.lock())
        {
        	sharedPtr->SetText(std::format("{:.1f}", m_FrameCount / m_Timer));
        }
       m_FrameCount = 0;
       m_Timer = 0.f;
    }
}
