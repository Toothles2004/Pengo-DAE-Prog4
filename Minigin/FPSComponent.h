#pragma once
#include "BasicComponent.h"
#include "TextComponent.h"

class FPSComponent : public TextComponent
{
public:
    using TextComponent::TextComponent;

    void Update() override;

private:
    float m_RefreshRate = 0.1f;
    float m_Timer{ m_RefreshRate };

};

