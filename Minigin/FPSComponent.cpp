#include "FPSComponent.h"

#include "GameTime.h"
#include "TextComponent.h"

void FPSComponent::Update()
{
    const float deltaT = GameTime::GetDeltaTime();
    if (deltaT <= 0.f)
    {
        return;
    }

    m_Timer += deltaT;

    if (m_Timer >= m_RefreshRate)
    {
        m_Timer = 0.f;
        float fps{ 1.f / deltaT };

        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << fps;
        std::string s = stream.str() + " FPS";

        SetText(s);
    }
    TextComponent::Update();
}
