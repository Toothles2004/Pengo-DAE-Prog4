#pragma once
#include "BasicComponent.h"
#include "TextComponent.h"

class FPSComponent : public BasicComponent
{
public:
    explicit FPSComponent(dae::GameObject* owner);

    void Update() override;

private:
    float m_RefreshRate;
    float m_Timer;
    float m_FrameCount;
    std::weak_ptr<TextComponent> m_pTextComponent;

};

