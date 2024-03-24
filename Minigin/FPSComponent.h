#pragma once
#include "BasicComponent.h"
#include "TextComponent.h"

class FPSComponent : public daeEngine::BasicComponent
{
public:
    explicit FPSComponent(dae::GameObject* owner);

    void Update() override;

private:
    float m_RefreshRate;
    float m_Timer;
    float m_FrameCount;
    TextComponent* m_pTextComponent;

};

